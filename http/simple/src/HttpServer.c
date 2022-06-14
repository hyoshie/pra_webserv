#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define SIZE (5 * 1024)

#ifndef DEBUG
#define DEBUG 0
#endif

void	DieWithError(char *errormessage);

static int	RecvRequestMessage(int clntSock, char *requestMessage, unsigned int bufSize)
{
	int	recvMsgSize;

	recvMsgSize = recv(clntSock, requestMessage, bufSize, 0);

	return recvMsgSize;
}

//リクエストメッセージを解析する
//第三引数のメッセージを読み取って、第一引数と第二引数にデータを格納する
static int	ParseRequestMessage(char *method, char *target,  char *requestMessage)
{
	char	*line;
	char	*tmpMethod;
	char	*tmpTarget;

	line = strtok(requestMessage, "\n");

	tmpMethod = strtok(line, " ");
	if (tmpMethod == NULL)
	{
		printf("get method error\n");
		return (-1);
	}
	strcpy(method, tmpMethod);

	tmpTarget = strtok(NULL, " ");
	if (tmpTarget == NULL)
	{
		printf("get target error\n");
		return (-1);
	}
	strcpy(target, tmpTarget);

	return 0;
}

//ファイルサイズを取得する
static unsigned int	GetFileSize(const char *path)
{
	int	size;
	int	readSize;
	char	readBuf[SIZE];
	FILE	*f;

	f = fopen(path, "rb");
	if (f  ==  NULL)
		return 0;

	size = 0;
	do {
		readSize = fread(readBuf, 1, SIZE, f);
		size += readSize;
	} while (readSize != 0);

	fclose(f);

	return size;
}

//リクエストに対する処理を行う
//今回はGETのみ
//filePathの内容をbodyに格納する
//戻り値はステータスコード
static int	GetProcessing(char *body,  char *filePath)
{
	FILE	*f;
	int	fileSize;

	fileSize = GetFileSize(filePath);
	if (fileSize == 0)
	{
		printf("GetFileSize() error\n");
		return 404;
	}
	f = fopen(filePath, "r");
	fread(body, sizeof(char), fileSize, f);
	fclose(f);

	return 200;
}

//レスポンスメッセージを作成する
//第一引数にデータを格納する
//その他の引数は素材
static int	CreateResponseMessage(char *responseMessage, int status, char *header, char *body, unsigned int bodySize)
{
	unsigned int	noBodyLen;
	unsigned int	bodyLen;

	responseMessage[0] = '\0';

	if (status == 200)
	{
		sprintf(responseMessage, "HTTP/1.1 200 OK\r\n%s\r\n", header);

		noBodyLen = strlen(responseMessage);
		bodyLen = bodySize;

		memcpy(&responseMessage[noBodyLen], body, bodyLen);
	}
	else if (status == 404)
	{
		sprintf(responseMessage, "HTTP/1.1 404 Not Found\r\n%s\r\n", header);

		noBodyLen = strlen(responseMessage);
		bodyLen = 0;
	}
	else
	{
		printf("Not support status(%d)\n", status);
		return -1;
	}
	return noBodyLen + bodyLen;
}

static int	SendResponseMessage(int clntSock, char *responseMessage, unsigned int messageSize)
{
	int	sendMsgSize;

	sendMsgSize = send(clntSock, responseMessage, messageSize, 0);

	return sendMsgSize;
}

static void	ShowMessage(char *message, unsigned int size)
{
	unsigned int	i;

	for (int i = 0; i < size; i++) {
		putchar(message[i]);
	}
	printf("\n\n");
}

//1.リクエストメッセージを受信
//2.受信した文字列を解析
//3.解析後の処理
//4.レスポンスメッセージを作成
//5.レスポンスメッセージを送信
int	HttpServer(int clntSock)
{
	int	requestMessageSize;
	int	responseMessageSize;
	char	requestMessage[SIZE];
	char	responseMessage[SIZE];
	char	method[SIZE];
	char	target[SIZE];
	char	headerField[SIZE];
	char	body[SIZE];
	int	status;
	unsigned int	fileSize;
	for (;;)
	{
		//1.リクエストメッセージを受信
		requestMessageSize = RecvRequestMessage(clntSock, requestMessage, SIZE);
		if (requestMessageSize < 0)
		{
			DieWithError("RecvRequestMessage() failed");
		}

		if (requestMessageSize == 0)
		{
			printf("connection ended\n");
			break ;
		}

		if (DEBUG)
		{
			printf("##### Request Message#####\n");
			ShowMessage(requestMessage, requestMessageSize);
		}

		//2.受信した文字列を解析
		//メソッドやリクエストターゲットを取得
		if (ParseRequestMessage(method, target, requestMessage) < 0)
		{
			DieWithError("ParseRequestMessage() failed");
		}

		//3.解析後の処理
		if (strcmp(method, "GET") == 0)
		{
			if (strcmp(target, "/") == 0)
			{
				strcpy(target, "/index.html");
			}
			//最初の/を読み飛ばしている
			status = GetProcessing(body, &target[1]);
		}
		else
		{
			status = 404;
		}

		//ヘッダーフィールド作成
		//最初の/を読み飛ばしている
		fileSize = GetFileSize(&target[1]);
		sprintf(headerField, "Content-Length: %u\r\n", fileSize);

		//4.レスポンスメッセージを作成
		responseMessageSize = CreateResponseMessage(responseMessage, status, headerField, body, fileSize);
		if (responseMessageSize < 0)
		{
			DieWithError("CreateResponseMessage() failed");
		}

		if (DEBUG)
		{
			printf("##### Response Message#####\n");
			ShowMessage(responseMessage, responseMessageSize);
		}

		//5.レスポンスメッセージを送信
		SendResponseMessage(clntSock, responseMessage, responseMessageSize);
	}
}

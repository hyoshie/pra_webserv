./bin/server
./bin/client 127.0.0.1 $(python -c "print('a' * 65507)") 5000 //OK
./bin/client 127.0.0.1 $(python -c "print('a' * 65508**)") 5000 //NG

IPパケット65535バイト - IPヘッダ20バイト - UDPヘッダ2バイト= 65507

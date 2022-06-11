#include <stdio.h>
#include <pthread.h>

static int RETURN_CODE = 100;

void *doSomething(void *arg) {
    return &RETURN_CODE;
    // pthread_exit(&RETURN_CODE);
}

int main() {
    // スレッドの作成
    pthread_t handle;
    pthread_create(&handle, NULL, doSomething, NULL);

    // スレッドの終了ステータスを取得
    void *status;
    pthread_join(handle, &status);

    if (status == PTHREAD_CANCELED) {
        printf("Thread was canceled.\n");
    } else {
        int val = *((int*) status);
        printf("Return value = %d\n", val);
    }
}

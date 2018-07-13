#include <jni.h>
#include <unistd.h>

JavaVM *sVm = NULL;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    sVm = vm;
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_st_lowlevel_jni_pipe_Pipe_close(JNIEnv *env, jobject obj, jint fd) {
    close(fd);
}

JNIEXPORT jintArray JNICALL Java_st_lowlevel_jni_pipe_Pipe_create(JNIEnv *env, jobject obj) {
    jintArray result;
    int fd[2];

    if (pipe(fd) < 0) {
        return NULL;
    }

    result = (*env)->NewIntArray(env, 2);
    (*env)->SetIntArrayRegion(env, result, 0, 2, fd);

    return result;
}

JNIEXPORT jlong JNICALL Java_st_lowlevel_jni_pipe_Pipe_read(JNIEnv *env, jobject obj, jint fd, jbyteArray buffer, size_t size) {
    if (!buffer || size <= 0) {
        return -1;
    }

    jbyte *buf = (*env)->GetByteArrayElements(env, buffer, NULL);
    ssize_t result = read(fd, (uint8_t *)buf, size);

    (*env)->ReleaseByteArrayElements(env, buffer, buf, JNI_ABORT);

    return result;
}

JNIEXPORT jint JNICALL Java_st_lowlevel_jni_pipe_Pipe_select(JNIEnv *env, jobject obj, jint fd, jlong timeout) {
    fd_set set;
    struct timeval tv;

    FD_ZERO(&set);
    FD_SET(fd, &set);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    return select(fd + 1, &set, NULL, NULL, &tv);
}

JNIEXPORT jlong JNICALL Java_st_lowlevel_jni_pipe_Pipe_write(JNIEnv *env, jobject obj, jint fd, jbyteArray buffer, size_t size) {
    if (!buffer || size <= 0) {
        return -1;
    }

    jbyte *buf = (*env)->GetByteArrayElements(env, buffer, NULL);
    ssize_t result = write(fd, (uint8_t *)buf, size);

    (*env)->ReleaseByteArrayElements(env, buffer, buf, JNI_ABORT);

    return result;
}
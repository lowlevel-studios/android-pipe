package st.lowlevel.jni.pipe;

import android.support.annotation.NonNull;

import java.util.concurrent.TimeUnit;

public class Pipe {
    /*
     * Private variables
     */
    private int mReadFd  = -1;
    private int mWriteFd = -1;


    static {
        System.loadLibrary("pipe-jni");
    }


    /*
     * Native methods
     */
    private native void close(int fd);

    private native int[] create();

    private native long read(int fd, byte[] buffer, long size);

    private native int select(int fd, long timeout);

    private native long write(int fd, byte[] buffer, long size);


    /*
     * Public methods
     */
    public void close() {
        /* Close descriptors */
        if (mReadFd >= 0)
            close(mReadFd);

        if (mWriteFd >= 0)
            close(mWriteFd);

        /* Reset descriptors */
        mReadFd = mWriteFd = -1;
    }

    public int getReadDescriptor() {
        /* Return descriptor */
        return mReadFd;
    }

    public int getWriteDescriptor() {
        /* Return descriptor */
        return mWriteFd;
    }

    public boolean init() {
        /* Check if ready */
        if (isReady())
            return true;

        /* Create pipe */
        int[] fds = create();

        /* Check array */
        if (fds == null)
            return false;

        /* Set descriptors */
        mReadFd  = fds[0];
        mWriteFd = fds[1];

        /* Return success */
        return true;
    }

    public boolean isReady() {
        /* Check descriptors */
        return (mReadFd >= 0) && (mWriteFd >= 0);
    }

    public long read(byte[] buffer, long size) {
        /* Read data */
        return read(mReadFd, buffer, size);
    }

    public int select(long timeout) {
        /* Wait for I/O */
        return select(mReadFd, timeout);
    }

    public int select(int timeout, @NonNull TimeUnit tu) {
        /* Wait for I/O */
        return select(tu.toSeconds(timeout));
    }

    public long write(byte[] buffer, long size) {
        /* Write data */
        return write(mReadFd, buffer, size);
    }
}

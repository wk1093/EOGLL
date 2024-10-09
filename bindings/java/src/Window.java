class Window {
    public long w_window;

    public Window(int width, int height, String title, WindowHints hints) {
        w_window = w_create(width, height, title, hints.wh_hints);
    }

    protected void finalize() {
        w_destroy(w_window);
    }

    public boolean shouldClose() {
        return w_shouldClose(w_window);
    }

    public void setShouldClose(boolean shouldClose) {
        w_setShouldClose(w_window, shouldClose);
    }

    public void pollEvents() {
        w_pollEvents(w_window);
    }

    public void swapBuffers() {
        w_swapBuffers(w_window);
    }

    static {
		System.loadLibrary("eogll_window");
	}

    private static native long w_create(int width, int height, String title, long hints);
    private static native void w_destroy(long window);
    private static native boolean w_shouldClose(long window);
    private static native void w_setShouldClose(long window, boolean shouldClose);
    private static native void w_pollEvents(long window);
    private static native void w_swapBuffers(long window);
}
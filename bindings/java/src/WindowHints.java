class WindowHints {
    public long wh_hints;

    public WindowHints() {
        wh_hints = wh_create_default();
    }

    public WindowHints(boolean resizable, boolean decorated, boolean floating, boolean maximized, boolean visible, boolean focused, boolean transparent) {
        wh_hints = wh_create(resizable, decorated, floating, maximized, visible, focused, transparent);
    }

    protected void finalize() {
        wh_destroy(wh_hints);
    }

    public boolean resizable() {
        return wh_resizable(wh_hints);
    }
    public boolean decorated() {
        return wh_decorated(wh_hints);
    }
    public boolean floating() {
        return wh_floating(wh_hints);
    }
    public boolean maximized() {
        return wh_maximized(wh_hints);
    }
    public boolean visible() {
        return wh_visible(wh_hints);
    }
    public boolean focused() {
        return wh_focused(wh_hints);
    }
    public boolean transparent() {
        return wh_transparent(wh_hints);
    }

    static {
		System.loadLibrary("eogll_windowhints");
	}

    private static native long wh_create(boolean resizable, boolean decorated, boolean floating, boolean maximized, boolean visible, boolean focused, boolean transparent);
    private static native void wh_destroy(long hints);
    private static native boolean wh_resizable(long hints);
    private static native boolean wh_decorated(long hints);
    private static native boolean wh_floating(long hints);
    private static native boolean wh_maximized(long hints);
    private static native boolean wh_visible(long hints);
    private static native boolean wh_focused(long hints);
    private static native boolean wh_transparent(long hints);
    private static native long wh_create_default();
}
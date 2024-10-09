class Eogll {
    public static native int init();
    public static native void terminate();
    public static native String getVersionString();
    public static int SUCCESS = 0;
    
    static {
        System.loadLibrary("eogll_main");
    }

}
class Main {
    public static void main(String args[]) {
        WindowHints hints = new WindowHints();
        Window window = new Window(800, 600, "Hello World", hints);

        while (!window.shouldClose()) {
            window.pollEvents();
            window.swapBuffers();
        }
        Eogll.terminate();
    }
}
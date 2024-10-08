class Main {
    public static void main(String args[]) {
        System.out.println("Hello, World!");
        WindowHints hints = new WindowHints();
        System.out.println(hints.resizable());
        System.out.println(hints.decorated());
        System.out.println(hints.floating());
        System.out.println(hints.maximized());
        System.out.println(hints.visible());
        System.out.println(hints.focused());
        System.out.println(hints.transparent());
        hints = new WindowHints(true, true, true, true, true, true, true);
        System.out.println(hints.resizable());
        System.out.println(hints.decorated());
        System.out.println(hints.floating());
        System.out.println(hints.maximized());
        System.out.println(hints.visible());
        System.out.println(hints.focused());
        System.out.println(hints.transparent());
    }
}
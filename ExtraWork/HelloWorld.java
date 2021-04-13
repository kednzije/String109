public class HelloWorld {
    public static void main(String[] args) {
        int num = 10;
        int n = 10;
        num = n + (n++) + (++n);
        System.out.println(num);
    }
}
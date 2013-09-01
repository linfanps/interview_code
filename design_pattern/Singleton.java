//多线程下的单例
public class Singleton1 {
    private static Singleton1 instance = null;
    private Singleton1(){
        System.out.println("hello");
    }

    public static Singleton1 getInstance() {
        if (instance == null) {
            synchronized {
                if (instance == null) {
                    instance = new Singleton1();
                }
            }
        }

        return instance;
    }

    public static void main(String[] args) {
        Singleton1 example = Singleton1.getInstance();
    }
}
//利用静态初始化构造单例
class Singleton2 {
    private static Singleton2 instance = new Singleton2();
    private Singleton2() {
        System.out.println("hello");
    }

    public static Singleton2 getInstance {
        return instance;
    }
}

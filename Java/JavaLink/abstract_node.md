# 抽象链表

```java
abstract class A1{       //定义抽象类
    public abstract void println();
    private static class B1 extends A1{   //static定义的内部类属于外部类
        public void println(){              //覆写抽象类的方法
            System.out.println("更多课程请访问：www.youtk.com");
        }
    }
    public static A1 getInstance(){  //此方法可以通过类名直接找到
        return new B1();
    }
}
```

```java
abstract class A2{    //定义抽象类
    public A2(){                        //2.父类构造方法
        this.print2();                  //3.调用print2()方法
    }
    public abstract void print2();
}
class B2 extends A2{
    private int num = 100;
    public B2(int num){
        this.num = num;
    }
    public void print2(){               //4.调用覆写后的方法
        System.out.println("num = " + num);
    }
}
abstract class Action{
    //定义常量时必须保证两个内容相加的结果不是其他行为
    public static final int EAT = 1;
    public static final int SLEEP = 5;
    public static final int WORK = 7;
    /*
    * 控制操作的行为，所有行为都通过类的常量来描述。可以使用EAT,SLEEP,WORK
    * 或者进行命令的叠加使用
    * @param flag操作的行为标记*/
    public void command(int flag){
        switch(flag){
            case EAT :
                this.eat();     //调用子类的方法
                break;
            case SLEEP :
                this.sleep();   //调用子类的方法
                break;
            case WORK:
                this.work();    //调用子类的方法
                break;
            case EAT + WORK:
                this.eat();     //调用子类的方法
                this.work();    //调用子类的方法
                break;
        }
    }
    public abstract void eat();    //定义子类的操作标准
    public abstract void sleep();    //定义子类的操作标准
    public abstract void work();    //定义子类的操作标准
}
class Robot extends Action{
    public void eat(){
        System.out.println("机器人补充能量！！！");
    }
    public void sleep(){
    }
    public void work(){
        System.out.println("机器人正在努力工作！！！");
    }
}
class Humen extends Action{
    public void eat(){
        System.out.println("人类正在吃饭！！！");
    }
    public void sleep(){
        System.out.println("人类正在睡觉休息！！！");
    }
    public void work(){
        System.out.println("人为了梦想正在努力工作！！！");
    }
}
class Pig extends Action{
    public void eat(){
        System.out.println("猪正在啃食槽！！！");
    }
    public void sleep(){
        System.out.println("猪正在睡觉养膘！！！");
    }
    public void work(){
    }
}
interface AA{  //定义接口
    public static final String MSG = "YOOTK";   //全局常量
    public abstract void print();   //抽象方法
}
interface BB{  //定义接口
    public abstract void get();     //抽象方法
}
class X implements AA,BB{   //X类实现了两个接口
    public void print(){
        System.out.println("A接口的抽象方法！");
    }
    public void get(){
        System.out.println("B接口的抽象方法！");
    }
}
public class Testclass {
    public static void main(String[] args) {
        //此时取得抽象类对象时完全不知道B类这个子类的存在
        A1 a = A1.getInstance();
        a.println();   //调用被覆写的抽象方法
        new B2(30);                 //1.执行构造
        System.out.println();
        System.out.println("------------------------------");
        fun(new Robot());  //传递机器人行为子类
        fun(new Humen());   //传递人的行为子类
        fun(new Pig());   //传递猪的行为子类

        //向上转型
        AA aa = new X();
        X x = new X();
        //向上转型

        BB bb = x;

        //aa实际上代表的是X类对象

        BB bb1 = (BB) aa;

        //两次的实例均能调用B接口中的get方法

        aa.print();
        bb.get();
        bb1.get();
        //输出
        System.out.println(AA.MSG);
        System.out.println(aa instanceof AA);  //判断aa是否是AA接口实例，ture
        System.out.println(bb instanceof BB);
        System.out.println(bb1 instanceof BB);
    }
    public static void fun(Action act){
        act.command(Action.EAT);   //调用吃的操作
        act.command(Action.SLEEP);  //调睡的操作
        act.command(Action.WORK);  //调用工作的操作
    }
}
```
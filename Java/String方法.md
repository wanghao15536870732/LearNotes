# String类的基本概念：

```java
public class StringDemo{
    public static void main(String[] args) {
        String str = new String("www.Test.com");
        System.out.println(str);
        String sta = "Hello";
        String stb = new String("Hello");  //stb使用关键字new开辟了新的堆内空间
        String stc = stb;
        System.out.println(sta == stb); //false
        System.out.println(sta == stc); // false    //String 比较时比较的只是内存地址的数值,而不是内容
        System.out.println(stb == stc); // true       因为stb和stc指向的是同一个对内存中的"Hello",因此输出为true

        //使用equals进行的是字符串内容的比较

        System.out.println(sta.equals(stb));  //true
        System.out.println(sta.equals(stc));  //true
        System.out.println(stb.equals(stc));  //true


        String stra = "Hello";
        String strb = "Hello";
        String strc = "Hello";
        System.out.println(stra == strb);//每一个字符串都是一个String的匿名对象
        String str2 = new String("Hello");  //所以会首先在堆内存中开辟一块空间炮村字符串"Hello"
                                                    // 然后使用关键字new，开辟另一块对内存空间，这种构造方法
        System.out.println(stra == strc);          //true
        System.out.println(strb == strc);           //true


        String strd = new String("Hello");//此时不会自动保存到对象池中
        String stre = "Hello";                      //此时将开辟新的空间
        System.out.println(strd == stre);//         /结果为false

        String strd2 = new String("Hello").intern();//使用构造方法定义新的内存空间，手工入池
        String stre2 = "Hello";
        System.out.println(strd2 == stre2);    //结果为true
    }
}
```

+ String的部分方法:

```java
    char c = str.charAt(0); //截取第一个字符
    System.out.println(c);
```

```java
    char []date = str.toCharArray();                //将字符串变为字符数组
    for (int i = 0; i < date.length; i++) {
        System.out.print(date[i] + "->");           //  h->e->l->l->o->
    }
    System.out.println();
    for (int i = 0; i < date.length; i++) {
        date[i] -= 32;
    }
    System.out.println(new String(date));                   //将全部字符数组变为String HELLO
    System.out.println(new String(date,1,2));  //将部分字符数组变为String

```

``` java

    byte[]date1 = str.getBytes();                           //将字符串变为字节数组
    for (int i = 0; i < date1.length; i++) {
        date1[i] -= 32;
    }
    System.out.println(new String(date1));                  //HELLO
    System.out.println(new String(date1,2,2));//LL

//字符串的比较

    String strf = "Hello";
    System.out.println(str.equals(strf));           //false 区分大小写
    System.out.println(str.equalsIgnoreCase(strf));  //true 不区分大小写
    System.out.println(str.compareTo(strf));        //  32  比较的是两字符串的编码差值

    //字符串的查找
    System.out.println(str.indexOf("e")); // 1  返回的是满足条件单词的第一个字母的索引
    System.out.println(str.lastIndexOf("e"));// 3

```
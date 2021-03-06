---
title: Java第一行代码 学习笔记(一) 使用 Date 、SimpleDateForma和 Calendar 类表示时间
tags:
  - Java
  - Java第一行代码
categories: Java
top: 102
---
![u=56560423,3204706921&fm=26&gp=0.jpg](https://upload-images.jianshu.io/upload_images/9140378-8cac7b0210aa1c57.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

***
<!--more-->

### 在程序开发中，经常需要处理日期和时间的相关数据，此时我们可以使用 java.util 包中的 Date 类。
#### 这个类最主要的作用就是获取当前时间，我们来看下 Date 类的使用



```java
Date d = new Date();  //使用默认的构造方法创建Date对象
System,out.println(d);  //输出Date对象
```
+ 使用 Date 类的默认无参构造方法创建出的对象就代表当前时间，
我们可以直接输出 Date 对象显示当前的时间，
显示的结果如下：
```java
Wed Jun 11 09:22:30 CST 2014
```
+ 其中， Wed 代表 Wednesday (星期三)， Jun 代表 June (六月)，
11 代表 11 号， CST 代表 China Standard Time (中国标准时间，也就是北京时间，东八区)
+ 从上面的输出结果中，我们发现，默认的时间格式不是很友好，与我们日常看到的日期格式不太一样，如果想要按指定的格式进行显示，如 2014-06-11 09:22:30 ，那该怎么做呢？
+ 有两种方法

####  使用 format(...) 方法将日期转换为指定格式的文本
```java
//创建Date对象，表示当前时间
Date d = new Date();
//创建SimpleDateFormat对象，指定目标格式
SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//调用format()方法，格式化时间，转换为指定格式字符串
String today = sdf.format(d);
System.out.println(today);
代码中的 “yyyy-MM-dd HH:mm:ss” 为预定义字符串，
	yyyy 表示四位年， MM 表示两位月份， dd 表示两位日期， HH 表示小时(使用24小时制)， mm 表示分钟， ss 表示秒，
这样就指定了转换的目标格式，最后调用 format() 方法将时间转换为指定的格式的字符串。
```
+ 运行结果：
```java
2018-02-04 21:05:35  //即当前时间
```
#### 使用 parse() 方法将文本转换为日期
```java
//创建日期格式的字符串
String day = "2018年02月04日 21:26:30";
//创建SimpleDateFormat对象，指定字符串的日期格式
SimpleDateFormat df = new SimpleDateFormat("yyyy年MM月dd日 HH:mm:ss");
//调用parse方法，将字符串转换成日期
Date date = df.parse(day);
//输出转换之后的日期
System,out,println("当前时间" + date);
```
+  代码中的 “yyyy年MM月dd日 HH:mm:ss” 指定了字符串的日期格式，调用 parse() 方法将文本转换为日期
+ 运行结果：
```java
Sun Jun 01 21:05:36 CST 2014
```
#### 一定要注意 ! ! !
+ 调用 SimpleDateFormat 对象的 parse() 方法时可能会出现转换异常，即 ParseException ，因此需要进行异常处理
+ 使用 Date 类时需要导入 java.util 包，使用 SimpleDateFormat 时需要导入 java.text 包

####  此时就到了 java.text 包中的 SimpleDateFormat 类大显身手的时候了！！
+ 可以使用 SimpleDateFormat 来对日期时间进行格式化，如可以将日期转换为指定格式的文本，也可将文本转换为日期

```java
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class HelloWorld {

    public static void main(String[] args) throws ParseException {

		// 使用format()方法将日期转换为指定格式的文本
		SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy年MM月dd日 HH时mm分ss秒");
		SimpleDateFormat sdf2 = new SimpleDateFormat("yyyy/MM/dd HH:mm");
		SimpleDateFormat sdf3 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

		// 创建Date对象，表示当前时间
    Date now = new Date();

    // 调用format()方法，将日期转换为字符串并输出
		System.out.println(sdf1.format(now));
		System.out.println(sdf2.format(now));
		System.out.println(sdf3.format(now));

		// 使用parse()方法将文本转换为日期
		String d = "2014-6-1 21:05:36";
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    // 调用parse()方法，将字符串转换为日期
		Date date  = sdf.parse(d);

		System.out.println(date);
	}
}
```
+ 运行结果：
```java
2018年02月04日 21时05分35秒
2018/02/04 21:05
2018-02-04 21:05:35
Sun Jun 01 21:05:36 CST 2014
```
##### Date 类最主要的作用就是获得当前时间，同时这个类里面也具有设置时间以及一些其他的功能，但是由于本身设计的问题，这些方法却遭到众多批评，不建议使用，更推荐使用 Calendar 类进行时间和日期的处理
+ java.util.Calendar 类是一个抽象类，可以通过调用 getInstance() 静态方法获取一个 Calendar 对象
+ 此对象已由当前日期时间初始化，即默认代表当前时间，如 Calendar c = Calendar.getInstance()
+ 那么如何使用 Calendar 获取年、月、日、时间等信息呢？我们来看下面的代码：

```java
  Calendar c1 = Calendar.getInstance();  //创建Calendar对象
  int year = c1.get(Calendar.YEAR);
  int month = c1.get(Calendar.MONTH) + 1;  //获取月份，0表示1月份
  int day = c1.get(Calendar.DAY_OF_MONTH);
  int hour = c1.get(Calendar.HOUR_OF_DAY);
  int minute = c1.get(Calendar.MINUTE);
  int second = c1.get(Calendar.MINUTE);
  System.out.println("当前时间：" + year + "-" + month + "-" + day + "-"
+ hour + ":" + minute + ":" + second)
```
+ 其中，调用 Calendar 类的 getInstance() 方法获取一个实例，然后通过调用 get() 方法获取日期时间信息，参数为需要获得的字段的值，Calendar.Year 等为 Calendar 类中定义的静态常量
+  运行结果 ：
```java
 当前时间：2018-2-4-22:24:24
```
+ Calendar 类提供了 getTime() 方法，用来获取 Date 对象， 完成 Calendar 和 Date 的转换，还可通过 getTimeInMillis() 方法，获取此 Calendar 的时间值，以毫秒为单位。如下所示:
```java
  Date date = c.getTime();
  Long time = c.getTimeInMillis();
  System.out.println("******************");
  System.out.println("当前时间：" + date);
  System.out.println("当前毫秒数：" + time);
  System.out.println("*****************");
```
+ 运行结果 ：
```java
******************
当前时间：Sun Feb 04 22:32:21 CST 2018
当前毫秒数：1517754741009
*****************
```
***

Github Pages [hyyyrwang.github.io](https://github.com/wanghao15536870732/LearnNotes/blob/master/%E4%BD%BF%E7%94%A8%20Date%20%E5%92%8C%20SimpleDateFormat%20%E7%B1%BB%E8%A1%A8%E7%A4%BA%E6%97%B6%E9%97%B4)

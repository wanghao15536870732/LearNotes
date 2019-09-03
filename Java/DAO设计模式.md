# 第十五章：DAO设计模式

## 15.3  项目准备

### 范例15-1：定义数据库的连接类

```java
​```java
package com.yootk.dbc;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
/**
 * 本类专门负责数据库的连接与关闭操作，在实例化本类对象时就意味着要进行数据库的开发<br>
 * 所以在本类的构造方法里要进行数据库驱动加载与数据库连接取得
 */
public class DatabaseConnection { 
    private static final String DBDRIVER = "oracle.jdbc.driver.OracleDriver" ;
    private static final String DBURL = "jdbc:oracle:thin:@localhost:1521:yootk" ;
    private static final String DBUSER = "scott" ;
    private static final String PASSWORD = "tiger" ;
    private Connection conn = null ;
    /**
     * 在构造方法里面为conn对象进行实例化，可以直接取得数据库的连接对象<br>
     * 由于所有的操作都是基于数据库完成的，如果数据库无法取得连接，也就意味着所有的操作都可以停止了
     */
    public DatabaseConnection() {
        try {
            Class.forName(DBDRIVER) ;
            this.conn = DriverManager.getConnection(DBURL,DBUSER,PASSWORD) ;
        } catch (Exception e) {	// 虽然此处有异常，但是抛出的意义不大
            e.printStackTrace();
        }
    }
    /**
     * 取得一个数据库的连接对象
     * @return Connection实例化对象
     */
    public Connection getConnection() {
        return this.conn ;
    }
    /**
     * 负责数据库的关闭
     */
    public void close() {
        if (this.conn != null) {		// 表示存在连接对象
           try {
               this.conn.close();	// 关闭数据库连接
           } catch (SQLException e) {
               e.printStackTrace();
           }
        }
    }
}

​```

## 15.4  开发数据层

### 范例15-3：定义IEmpDAO接口

​```java
package com.yootk.dao;
import java.util.List;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * 定义emp表的数据层的操作标准
 */
public interface IEmpDAO {
    /**
     * 实现数据的增加操作
     * @param vo 包含了要增加数据的VO对象
     * @return 数据保存成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean doCreate(Emp vo) throws Exception ;
    /**
     * 实现数据的修改操作，本次修改是根据id进行全部字段数据的修改
     * @param vo 包含了要修改数据的信息，一定要提供ID内容
     * @return 数据修改成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean doUpdate(Emp vo) throws Exception ;
    /**
     * 执行数据的批量删除操作，所有要删除的数据以Set集合的形式保存
     * @param ids 包含了所有要删除的数据ID，不包含重复内容
     * @return 删除成功返回true（删除的数据个数与要删除的数据个数相同），否则返回false。
     * @throws Exception SQL执行异常
     */
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception ;
    /**
     * 根据雇员编号查询指定的雇员信息
     * @param id 要查询的雇员编号
     * @return 如果雇员信息存在，则将数据以VO类对象的形式返回，如果雇员数据不存在，则返回null
     * @throws Exception SQL执行异常
     */
    public Emp findById(Integer id) throws Exception ;
    /**
     * 查询指定数据表的全部记录，并且以集合的形式返回
     * @return 如果表中有数据，则所有的数据会封装为VO对象后利用List集合返回，<br>
     * 如果没有数据，那么集合的长度为0（size() == 0，不是null）
     * @throws Exception SQL执行异常
     */
    public List<Emp> findAll() throws Exception ;
    /**
     * 分页进行数据的模糊查询，查询结果以集合的形式返回
     * @param currentPage 当前所在的页
     * @param lineSize 每行显示数据行数
     * @param column 要进行模糊查询的数据列
     * @param keyWord 模糊查询的关键字
     * @return 如果表中有数据，则所有的数据会封装为VO对象后利用List集合返回，<br>
     * 如果没有数据，那么集合的长度为0（size() == 0，不是null）
     * @throws Exception SQL执行异常
     */
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception;
    /**
     * 进行模糊查询数据量的统计，如果表中没有记录，统计的结果就是0
     * @param column 要进行模糊查询的数据列
     * @param keyWord 模糊查询的关键字
     * @return 返回表中的数据量，如果没有数据返回0
     * @throws Exception SQL执行异常
     */
    public Integer getAllCount(String column,String keyWord) throws Exception ;
}

​```

## 范例15-4：EmpDAOImpl子类

​```javapackage com.yootk.dao.impl;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import com.yootk.dao.IEmpDAO;
import com.yootk.vo.Emp;
/**
 * 定义emp表的数据层的具体实现子类
 * @author 极限IT（www.jixianit.com）
 */
public class EmpDAOImpl implements IEmpDAO {// 实现IEmpDAO接口
    private Connection conn ;// 需要利用Connection对象操作
    private PreparedStatement pstmt ;// 定义数据库操作对象
    /*
     * 如果要使用数据层进行原子性的功能操作实现，必须要提供Connection接口对象<br>
     * 另外，由于开发中业务层要调用数据层，所以数据库的打开与关闭交由业务层处理
     * @param conn 表示数据库连接对象
     */
    public EmpDAOImpl(Connection conn) {// 传递Connection接口对象
        this.conn = conn ;// 保存数据库连接
    }
    @Override
    public boolean doCreate(Emp vo) throws Exception {
        String sql = "INSERT INTO emp(empno,ename,job,hiredate,sal,comm) VALUES (?,?,?,?,?,?)" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setInt(1, vo.getEmpno());// 设置字段内容
        this.pstmt.setString(2, vo.getEname());// 设置字段内容	
        this.pstmt.setString(3, vo.getJob());// 设置字段内容
        // 将java.util.Date类的对象转换为java.sql.Date类对象
        this.pstmt.setDate(4, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(5, vo.getSal());// 设置字段内容
        this.pstmt.setDouble(6, vo.getComm());// 设置字段内容
        return this.pstmt.executeUpdate() > 0 ;// 执行数据更新操作
    }
    @Override
    public boolean doUpdate(Emp vo) throws Exception {
        String sql = "UPDATE emp SET ename=?,job=?,hiredate=?,sal=?,comm=? WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setString(1, vo.getEname());// 设置字段内容
        this.pstmt.setString(2, vo.getJob());// 设置字段内容
        // 将java.util.Date类的对象转换为java.sql.Date类对象
        this.pstmt.setDate(3, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(4, vo.getSal());// 设置字段内容
        this.pstmt.setDouble(5, vo.getComm());// 设置字段内容
        this.pstmt.setInt(6, vo.getEmpno());// 设置字段内容
        return this.pstmt.executeUpdate() > 0 ;// 执行数据更新操作
    }
    @Override
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception {
        StringBuffer sql = new StringBuffer() ;// 拼凑SQL
        sql.append("DELETE FROM emp WHERE empno IN(") ;// 追加SQL语句
        Iterator<Integer> iter = ids.iterator() ;// 迭代每一个删除ID
        while (iter.hasNext()) {
            sql.append(iter.next()).append(",") ;// 追加SQL
        }
        sql.delete(sql.length()-1, sql.length()).append(")") ;// 处理SQL
        this.pstmt = this.conn.prepareStatement(sql.toString()) ;// 创建数据库操作对象
        return this.pstmt.executeUpdate() == ids.size();// 执行数据更新操作
    }
    @Override
    public Emp findById(Integer id) throws Exception {
        Emp vo = null ;// 定义VO对象
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// 创建数据库操作对象
        this.pstmt.setInt(1, id);// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        if (rs.next()) {// 已经找到数据
           vo = new Emp() ;// 实例化VO对象
           vo.setEmpno(rs.getInt(1));// 读取列内容并将数据保存在属性中
           vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
           vo.setJob(rs.getString(3));// 读取列内容并将数据保存在属性中
           vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
           vo.setSal(rs.getDouble(5));						// 读取列内容并将数据保存在属性中
           vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
        }
        return vo ;									// 返回VO类对象
    }
    @Override
    public List<Emp> findAll() throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// 实例化集合对象
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// 创建数据库操作对象
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        while (rs.next()) {								// 有多条数据返回，循环多次
            Emp vo = new Emp() ;						// 实例化VO对象
            vo.setEmpno(rs.getInt(1));					// 读取列内容并将数据保存在属性中
            vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
            vo.setJob(rs.getString(3));					// 读取列内容并将数据保存在属性中
            vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
            vo.setSal(rs.getDouble(5));					// 读取列内容并将数据保存在属性中
            vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
            all.add(vo) ;								// 向集合保存数据
        }
        return all;									// 返回集合
    }
    @Override
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// 定义集合
        String sql = "SELECT * FROM " + 
                   " (SELECT empno,ename,job,hiredate,sal,comm,ROWNUM rn" + 
                   " FROM emp" + " WHERE " + column + " LIKE ? AND ROWNUM<=?) temp " + 
                   " WHERE temp.rn>? "; 				// 执行SQL分页语句
        this.pstmt = this.conn.prepareStatement(sql) ;	// 创建数据库操作对象
        this.pstmt.setString(1, "%" + keyWord + "%");		// 设置字段内容
        this.pstmt.setInt(2, currentPage * lineSize);	// 设置字段内容
        this.pstmt.setInt(3, (currentPage - 1) * lineSize); 		// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        while (rs.next()) {								// 循环取出每一行数据
            Emp vo = new Emp() ;						// 实例化VO对象
            vo.setEmpno(rs.getInt(1));					// 读取列内容并将数据保存在属性中
            vo.setEname(rs.getString(2));					// 读取列内容并将数据保存在属性中
            vo.setJob(rs.getString(3));					// 读取列内容并将数据保存在属性中
            vo.setHiredate(rs.getDate(4));					// 读取列内容并将数据保存在属性中
            vo.setSal(rs.getDouble(5));					// 读取列内容并将数据保存在属性中
            vo.setComm(rs.getDouble(6));					// 读取列内容并将数据保存在属性中
            all.add(vo) ;								// 向集合保存数据
        }
        return all;									// 返回List集合数据
    }
    @Override
    public Integer getAllCount(String column, String keyWord) throws Exception {
        String sql = "SELECT COUNT(empno) FROM emp WHERE " + column + " LIKE ?" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// 创建数据库操作对象
        this.pstmt.setString(1, "%" + keyWord + "%");		// 设置字段内容
        ResultSet rs = this.pstmt.executeQuery() ;			// 执行数据查询操作
        if (rs.next()) {								// COUNT()统计一定会返回结果
           return rs.getInt(1) ;							// 返回读取的第一列数据
        }
        return 0;									// 如果没有数据返回0
    }
}

​```

## 范例15-5：定义工厂类

​```java
package com.yootk.factory;
import java.sql.Connection;
import com.yootk.dao.IEmpDAO;
import com.yootk.dao.impl.EmpDAOImpl;
/**
 * 定义DAO工厂类，以后的DAO接口对象将通过此工厂类取得
 */
public class DAOFactory {
    /**
     * 取得IEmpDAO接口对象，通过EmpDAOImpl子类实例化
     * @param conn EmpDAOImpl构造方法需要接收数据库连接对象
     * @return IEmpDAO接口实例化对象
     */
    public static IEmpDAO getIEmpDAOInstance(Connection conn) {
        return new EmpDAOImpl(conn) ;			// 实例化EmpDAOImpl子类对象
    }
}

​```

## 15.5  开发业务层

### 范例15-6：定义IEmpService操作标准。

​```java
package com.yootk.service;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * 定义emp表的业务层的执行标准，此类一定要负责数据库的打开与关闭操作
 * 此类可以通过DAOFactory类取得IEmpDAO接口对象
 */
public interface IEmpService {
    /**
     * 实现雇员数据的增加操作，本次操作要调用IEmpDAO接口的方法：<br>
     * <li>需要调用IEmpDAO.findById()方法，判断要增加数据的id是否已经存在；</li>
     * <li>如果要增加的数据编号不存在，则调用IEmpDAO.doCreate()方法，返回操作的结果。</li>
     * @param vo 包含了要增加数据的VO对象
     * @return 如果增加数据的ID重复或保存失败，则返回false，否则返回true
     * @throws Exception SQL执行异常
     */
    public boolean insert(Emp vo) throws Exception ;
    /**
     * 实现雇员数据的修改操作，本次要调用IEmpDAO.doUpdate()方法，本次修改属于全部内容的修改
     * @param vo 包含了要修改数据的VO对象
     * @return 修改成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean update(Emp vo) throws Exception ;
    /**
     * 执行雇员数据的删除操作，可以删除多个雇员信息，调用IEmpDAO.doRemoveBatch()方法
     * @param ids 包含了全部要删除数据的集合，没有重复数据
     * @return 删除成功返回true，否则返回false
     * @throws Exception SQL执行异常
     */
    public boolean delete(Set<Integer> ids) throws Exception ;
    /**
     * 根据雇员编号查找雇员的完整信息，调用IEmpDAO.findById()方法
     * @param ids 要查找的雇员编号
     * @return 如果找到了，则将雇员信息以VO对象返回，否则返回null
     * @throws Exception SQL执行异常
     */
    public Emp get(int ids) throws Exception ;
    /**
     * 查询全部雇员信息，调用IEmpDAO.findAll()方法
     * @return 查询结果以List集合的形式返回，如果没有数据则集合的长度为0
     * @throws Exception SQL执行异常
     */
    public List<Emp> list() throws Exception ;
    /**
     * 实现数据的模糊查询与数据统计，要调用IEmpDAO接口的两个方法：<br>
     * <li>调用IEmpDAO.findAllSplit()方法，查询所有的表数据，返回的是List<Emp>；</li>
     * <li>调用IEmpDAO.getAllCount()方法，查询所有的数据量，返回的是Integer；</li>
     * @param currentPage 当前所在页
     * @param lineSize 每页显示的记录数
     * @param column 模糊查询的数据列
     * @param keyWord 模糊查询关键字
     * @return 本方法由于需要返回多种数据类型，所以使用Map集合返回，由于类型不统一，所以所有value的类型设置为Object，返回内容如下。<br>
     * <li>key = allEmps，value = IEmpDAO.findAllSplit()返回结果（List<Emp>类型）</li>
     * <li>key = empCount，value = IEmpDAO.getAllCount()返回结果（Integer类型）</li>
     * @throws Exception SQL执行异常
     */
    public Map<String, Object> list(int currentPage, int lineSize, String column, String keyWord) throws Exception;
}

​```

### 范例15-7：定义EmpServiceImpl子类

​```java
package com.yootk.service.impl;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.dbc.DatabaseConnection;
import com.yootk.factory.DAOFactory;
import com.yootk.service.IEmpService;
import com.yootk.vo.Emp;
public class EmpServiceImpl implements IEmpService {
    // 在这个类的对象内部提供了一个数据库连接类的实例化对象
    private DatabaseConnection dbc = new DatabaseConnection();
    @Override
    public boolean insert(Emp vo) throws Exception {
        try {
            // 要增加的雇员编号如果不存在，则findById()返回的结果就是null
            // null表示可以保存新增雇员数据
            if (DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                     .findById(vo.getEmpno()) == null) {
            // 直接返回IEmpDAO.doCreate()方法的处理结果
               return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doCreate(vo);
            }
            return false;					// 增加失败
        } catch (Exception e) {
            throw e;						// 有异常交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public boolean update(Emp vo) throws Exception {
        try {// 更新操作将根据id进行全部更新，此处将直接返回数据层处理结果
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doUpdate(vo);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public boolean delete(Set<Integer> ids) throws Exception {
        try {
            if (ids == null || ids.size() == 0) {	// 没有要删除的数据
               return false ;				// 直接返回false
            }
            // 如果此时集合内容不为空，则调用数据层实现数据删除处理
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doRemoveBatch(ids);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public Emp get(int ids) throws Exception {
        try {
            // 直接调用数据层返回指定id的数据
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findById(ids);
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public List<Emp> list() throws Exception {
        try {
            // 直接调用数据层返回emp表的全部记录
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findAll();
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
    @Override
    public Map<String, Object> list(int currentPage, int lineSize, String column, 
        String keyWord)  throws Exception {
        try {
            // 由于此方法需要返回多种类型的数据，所以使用Map集合保存返回数据
            Map<String, Object> map = new HashMap<String, Object>();
            // 分页查询出emp表中的部分数据内容
            map.put("allEmps", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .findAllSplit(currentPage, lineSize, column, keyWord));
            // 统计出emp表中的数据量
            map.put("empCount", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .getAllCount(column, keyWord));
            return map; 
        } catch (Exception e) {
            throw e;						// 如果有异常，交给被调用处进行处理
        } finally {
            this.dbc.close();				// 不管数据层操作是否有异常，一定要关闭数据库连接
        }
    }
}

​```

### 范例15-8：定义ServiceFactory

​```java
package com.yootk.factory;
import com.yootk.service.IEmpService;
import com.yootk.service.impl.EmpServiceImpl;
public class ServiceFactory {
    /**
     * 取得IEmpService接口对象
     * @return IEmpService接口的实例化对象
     */
    public static IEmpService getIEmpServiceInstance() {
        return new EmpServiceImpl();
    }
}

​```
```

## 15.4  ĺźĺć°ćŽĺą

### čäž15-3ďźĺŽäšIEmpDAOćĽĺŁ

```java
package com.yootk.dao;
import java.util.List;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * ĺŽäšempčĄ¨çć°ćŽĺąçćä˝ć ĺ
 */
public interface IEmpDAO {
    /**
     * ĺŽç°ć°ćŽçĺ˘ĺ ćä˝?
     * @param vo ĺĺŤäşčŚĺ˘ĺ ć°ćŽçVOĺŻščąĄ
     * @return ć°ćŽäżĺ­ćĺčżĺtrueďźĺŚĺčżĺfalse
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean doCreate(Emp vo) throws Exception ;
    /**
     * ĺŽç°ć°ćŽçäżŽćšćä˝ďźćŹćŹĄäżŽćšćŻć šćŽidčżčĄĺ¨é¨ĺ­ćŽľć°ćŽçäżŽć?
     * @param vo ĺĺŤäşčŚäżŽćšć°ćŽçäżĄćŻďźä¸ĺŽčŚćäžIDĺĺŽš
     * @return ć°ćŽäżŽćšćĺčżĺtrueďźĺŚĺčżĺfalse
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean doUpdate(Emp vo) throws Exception ;
    /**
     * ć§čĄć°ćŽçćšéĺ é¤ćä˝ďźććčŚĺ é¤çć°ćŽäťĽSetéĺçĺ˝˘ĺźäżĺ­?
     * @param ids ĺĺŤäşććčŚĺ é¤çć°ćŽIDďźä¸ĺĺŤéĺ¤ĺĺŽš
     * @return ĺ é¤ćĺčżĺtrueďźĺ é¤çć°ćŽä¸Şć°ä¸čŚĺ é¤çć°ćŽä¸Şć°ç¸ĺďźďźĺŚĺčżĺfalseă?
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception ;
    /**
     * ć šćŽéĺçźĺˇćĽčŻ˘ćĺŽçéĺäżĄć?
     * @param id čŚćĽčŻ˘çéĺçźĺˇ
     * @return ĺŚćéĺäżĄćŻĺ­ĺ¨ďźĺĺ°ć°ćŽäťĽVOçąťĺŻščąĄçĺ˝˘ĺźčżĺďźĺŚćéĺć°ćŽä¸ĺ­ĺ¨ďźĺčżĺnull
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public Emp findById(Integer id) throws Exception ;
    /**
     * ćĽčŻ˘ćĺŽć°ćŽčĄ¨çĺ¨é¨čŽ°ĺ˝ďźĺšśä¸äťĽéĺçĺ˝˘ĺźčżĺ?
     * @return ĺŚćčĄ¨ä¸­ćć°ćŽďźĺććçć°ćŽäźĺ°čŁä¸şVOĺŻščąĄĺĺŠç¨Listéĺčżĺďź?<br>
     * ĺŚćć˛Ąćć°ćŽďźéŁäšéĺçéżĺşŚä¸?0ďźsize() == 0ďźä¸ćŻnullďź?
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public List<Emp> findAll() throws Exception ;
    /**
     * ĺéĄľčżčĄć°ćŽçć¨ĄçłćĽčŻ˘ďźćĽčŻ˘çťćäťĽéĺçĺ˝˘ĺźčżĺ
     * @param currentPage ĺ˝ĺćĺ¨çéĄ?
     * @param lineSize ćŻčĄćžç¤şć°ćŽčĄć°
     * @param column čŚčżčĄć¨ĄçłćĽčŻ˘çć°ćŽĺ?
     * @param keyWord ć¨ĄçłćĽčŻ˘çĺłéŽĺ­
     * @return ĺŚćčĄ¨ä¸­ćć°ćŽďźĺććçć°ćŽäźĺ°čŁä¸şVOĺŻščąĄĺĺŠç¨Listéĺčżĺďź?<br>
     * ĺŚćć˛Ąćć°ćŽďźéŁäšéĺçéżĺşŚä¸?0ďźsize() == 0ďźä¸ćŻnullďź?
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception;
    /**
     * čżčĄć¨ĄçłćĽčŻ˘ć°ćŽéççťčŽĄďźĺŚćčĄ¨ä¸­ć˛ĄćčŽ°ĺ˝ďźçťčŽĄççťćĺ°ąć?0
     * @param column čŚčżčĄć¨ĄçłćĽčŻ˘çć°ćŽĺ?
     * @param keyWord ć¨ĄçłćĽčŻ˘çĺłéŽĺ­
     * @return čżĺčĄ¨ä¸­çć°ćŽéďźĺŚćć˛Ąćć°ćŽčżĺ?0
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public Integer getAllCount(String column,String keyWord) throws Exception ;
}

```

## čäž15-4ďźEmpDAOImplĺ­çąť

```java
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import com.yootk.dao.IEmpDAO;
import com.yootk.vo.Emp;
/**
 * ĺŽäšempčĄ¨çć°ćŽĺąçĺˇä˝ĺŽç°ĺ­çąť
 * @author ćéITďźwww.jixianit.comďź?
 */
public class EmpDAOImpl implements IEmpDAO {// ĺŽç°IEmpDAOćĽĺŁ
    private Connection conn ;// éčŚĺŠç¨ConnectionĺŻščąĄćä˝
    private PreparedStatement pstmt ;// ĺŽäšć°ćŽĺşćä˝ĺŻščą?
    /*
     * ĺŚćčŚä˝żç¨ć°ćŽĺąčżčĄĺĺ­ć§çĺč˝ćä˝ĺŽç°ďźĺżéĄťčŚćäžConnectionćĽĺŁĺŻščąĄ<br>
     * ĺŚĺ¤ďźçąäşĺźĺä¸­ä¸ĺĄĺąčŚč°ç¨ć°ćŽĺąďźćäťĽć°ćŽĺşçćĺźä¸ĺłé­äş¤çąä¸ĺĄĺąĺ¤ç
     * @param conn čĄ¨ç¤şć°ćŽĺşčżćĽĺŻščą?
     */
    public EmpDAOImpl(Connection conn) {// äź éConnectionćĽĺŁĺŻščąĄ
        this.conn = conn ;// äżĺ­ć°ćŽĺşčżć?
    }
    @Override
    public boolean doCreate(Emp vo) throws Exception {
        String sql = "INSERT INTO emp(empno,ename,job,hiredate,sal,comm) VALUES (?,?,?,?,?,?)" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        this.pstmt.setInt(1, vo.getEmpno());// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setString(2, vo.getEname());// čŽžç˝Žĺ­ćŽľĺĺŽš	
        this.pstmt.setString(3, vo.getJob());// čŽžç˝Žĺ­ćŽľĺĺŽš
        // ĺ°java.util.DateçąťçĺŻščąĄč˝Źć˘ä¸şjava.sql.DateçąťĺŻščą?
        this.pstmt.setDate(4, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(5, vo.getSal());// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setDouble(6, vo.getComm());// čŽžç˝Žĺ­ćŽľĺĺŽš
        return this.pstmt.executeUpdate() > 0 ;// ć§čĄć°ćŽć´ć°ćä˝
    }
    @Override
    public boolean doUpdate(Emp vo) throws Exception {
        String sql = "UPDATE emp SET ename=?,job=?,hiredate=?,sal=?,comm=? WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        this.pstmt.setString(1, vo.getEname());// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setString(2, vo.getJob());// čŽžç˝Žĺ­ćŽľĺĺŽš
        // ĺ°java.util.DateçąťçĺŻščąĄč˝Źć˘ä¸şjava.sql.DateçąťĺŻščą?
        this.pstmt.setDate(3, new java.sql.Date(vo.getHiredate().getTime()));
        this.pstmt.setDouble(4, vo.getSal());// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setDouble(5, vo.getComm());// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setInt(6, vo.getEmpno());// čŽžç˝Žĺ­ćŽľĺĺŽš
        return this.pstmt.executeUpdate() > 0 ;// ć§čĄć°ćŽć´ć°ćä˝
    }
    @Override
    public boolean doRemoveBatch(Set<Integer> ids) throws Exception {
        StringBuffer sql = new StringBuffer() ;// ćźĺSQL
        sql.append("DELETE FROM emp WHERE empno IN(") ;// čż˝ĺ SQLčŻ­ĺĽ
        Iterator<Integer> iter = ids.iterator() ;// čż­äťŁćŻä¸ä¸Şĺ é¤ID
        while (iter.hasNext()) {
            sql.append(iter.next()).append(",") ;// čż˝ĺ SQL
        }
        sql.delete(sql.length()-1, sql.length()).append(")") ;// ĺ¤çSQL
        this.pstmt = this.conn.prepareStatement(sql.toString()) ;// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        return this.pstmt.executeUpdate() == ids.size();// ć§čĄć°ćŽć´ć°ćä˝
    }
    @Override
    public Emp findById(Integer id) throws Exception {
        Emp vo = null ;// ĺŽäšVOĺŻščąĄ
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp WHERE empno=?" ;
        this.pstmt = this.conn.prepareStatement(sql) ;// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        this.pstmt.setInt(1, id);// čŽžç˝Žĺ­ćŽľĺĺŽš
        ResultSet rs = this.pstmt.executeQuery() ;			// ć§čĄć°ćŽćĽčŻ˘ćä˝
        if (rs.next()) {// ĺˇ˛çťćžĺ°ć°ćŽ
           vo = new Emp() ;// ĺŽäžĺVOĺŻščąĄ
           vo.setEmpno(rs.getInt(1));// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
           vo.setEname(rs.getString(2));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
           vo.setJob(rs.getString(3));// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
           vo.setHiredate(rs.getDate(4));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
           vo.setSal(rs.getDouble(5));						// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
           vo.setComm(rs.getDouble(6));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
        }
        return vo ;									// čżĺVOçąťĺŻščą?
    }
    @Override
    public List<Emp> findAll() throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// ĺŽäžĺéĺĺŻščą?
        String sql = "SELECT empno,ename,job,hiredate,sal,comm FROM emp" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        ResultSet rs = this.pstmt.executeQuery() ;			// ć§čĄć°ćŽćĽčŻ˘ćä˝
        while (rs.next()) {								// ćĺ¤ćĄć°ćŽčżĺďźĺžŞçŻĺ¤ćŹĄ
            Emp vo = new Emp() ;						// ĺŽäžĺVOĺŻščąĄ
            vo.setEmpno(rs.getInt(1));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setEname(rs.getString(2));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setJob(rs.getString(3));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setHiredate(rs.getDate(4));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setSal(rs.getDouble(5));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setComm(rs.getDouble(6));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            all.add(vo) ;								// ĺéĺäżĺ­ć°ć?
        }
        return all;									// čżĺéĺ
    }
    @Override
    public List<Emp> findAllSplit(Integer currentPage, Integer lineSize, String column, String keyWord) throws Exception {
        List<Emp> all = new ArrayList<Emp>() ;			// ĺŽäšéĺ
        String sql = "SELECT * FROM " + 
                   " (SELECT empno,ename,job,hiredate,sal,comm,ROWNUM rn" + 
                   " FROM emp" + " WHERE " + column + " LIKE ? AND ROWNUM<=?) temp " + 
                   " WHERE temp.rn>? "; 				// ć§čĄSQLĺéĄľčŻ­ĺĽ
        this.pstmt = this.conn.prepareStatement(sql) ;	// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        this.pstmt.setString(1, "%" + keyWord + "%");		// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setInt(2, currentPage * lineSize);	// čŽžç˝Žĺ­ćŽľĺĺŽš
        this.pstmt.setInt(3, (currentPage - 1) * lineSize); 		// čŽžç˝Žĺ­ćŽľĺĺŽš
        ResultSet rs = this.pstmt.executeQuery() ;			// ć§čĄć°ćŽćĽčŻ˘ćä˝
        while (rs.next()) {								// ĺžŞçŻĺĺşćŻä¸čĄć°ć?
            Emp vo = new Emp() ;						// ĺŽäžĺVOĺŻščąĄ
            vo.setEmpno(rs.getInt(1));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setEname(rs.getString(2));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setJob(rs.getString(3));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setHiredate(rs.getDate(4));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setSal(rs.getDouble(5));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            vo.setComm(rs.getDouble(6));					// čŻťĺĺĺĺŽšĺšśĺ°ć°ćŽäżĺ­ĺ¨ĺąć§ä¸­
            all.add(vo) ;								// ĺéĺäżĺ­ć°ć?
        }
        return all;									// čżĺListéĺć°ćŽ
    }
    @Override
    public Integer getAllCount(String column, String keyWord) throws Exception {
        String sql = "SELECT COUNT(empno) FROM emp WHERE " + column + " LIKE ?" ;
        this.pstmt = this.conn.prepareStatement(sql) ; 		// ĺĺťşć°ćŽĺşćä˝ĺŻščą?
        this.pstmt.setString(1, "%" + keyWord + "%");		// čŽžç˝Žĺ­ćŽľĺĺŽš
        ResultSet rs = this.pstmt.executeQuery() ;			// ć§čĄć°ćŽćĽčŻ˘ćä˝
        if (rs.next()) {								// COUNT()çťčŽĄä¸ĺŽäźčżĺçťć
           return rs.getInt(1) ;							// čżĺčŻťĺççŹŹä¸ĺć°ć?
        }
        return 0;									// ĺŚćć˛Ąćć°ćŽčżĺ0 
    }
}

```

## čäž15-5ďźĺŽäšĺˇĽĺçąť

```java
package com.yootk.factory;
import java.sql.Connection;
import com.yootk.dao.IEmpDAO;
import com.yootk.dao.impl.EmpDAOImpl;
/**
 * ĺŽäšDAOĺˇĽĺçąťďźäťĽĺçDAOćĽĺŁĺŻščąĄĺ°éčżć­¤ĺˇĽĺçąťĺĺž
 */
public class DAOFactory {
    /**
     * ĺĺžIEmpDAOćĽĺŁĺŻščąĄďźéčżEmpDAOImplĺ­çąťĺŽäžĺ?
     * @param conn EmpDAOImplćé ćšćłéčŚćĽćść°ćŽĺşčżćĽĺŻščąĄ
     * @return IEmpDAOćĽĺŁĺŽäžĺĺŻščą?
     */
    public static IEmpDAO getIEmpDAOInstance(Connection conn) {
        return new EmpDAOImpl(conn) ;			// ĺŽäžĺEmpDAOImplĺ­çąťĺŻščąĄ
    }
}

```

## 15.5  ĺźĺä¸ĺĄĺą

### čäž15-6ďźĺŽäšIEmpServicećä˝ć ĺă?

```java
package com.yootk.service;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.vo.Emp;
/**
 * ĺŽäšempčĄ¨çä¸ĺĄĺąçć§čĄć ĺďźć­¤çąťä¸ĺŽčŚč´č´Łć°ćŽĺşçćĺźä¸ĺłé­ćä˝?
 * ć­¤çąťĺŻäťĽéčżDAOFactoryçąťĺĺžIEmpDAOćĽĺŁĺŻščąĄ
 */
public interface IEmpService {
    /**
     * ĺŽç°éĺć°ćŽçĺ˘ĺ ćä˝ďźćŹćŹĄćä˝čŚč°ç¨IEmpDAOćĽĺŁçćšćłďź<br>
     * <li>éčŚč°ç¨IEmpDAO.findById()ćšćłďźĺ¤ć­čŚĺ˘ĺ ć°ćŽçidćŻĺŚĺˇ˛çťĺ­ĺ¨ďź?</li>
     * <li>ĺŚćčŚĺ˘ĺ çć°ćŽçźĺˇä¸ĺ­ĺ¨ďźĺč°ç¨IEmpDAO.doCreate()ćšćłďźčżĺćä˝ççťćă?</li>
     * @param vo ĺĺŤäşčŚĺ˘ĺ ć°ćŽçVOĺŻščąĄ
     * @return ĺŚćĺ˘ĺ ć°ćŽçIDéĺ¤ćäżĺ­ĺ¤ąč´ĽďźĺčżĺfalseďźĺŚĺčżĺtrue
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean insert(Emp vo) throws Exception ;
    /**
     * ĺŽç°éĺć°ćŽçäżŽćšćä˝ďźćŹćŹĄčŚč°ç¨IEmpDAO.doUpdate()ćšćłďźćŹćŹĄäżŽćšĺąäşĺ¨é¨ĺĺŽšçäżŽćš
     * @param vo ĺĺŤäşčŚäżŽćšć°ćŽçVOĺŻščąĄ
     * @return äżŽćšćĺčżĺtrueďźĺŚĺčżĺfalse
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean update(Emp vo) throws Exception ;
    /**
     * ć§čĄéĺć°ćŽçĺ é¤ćä˝ďźĺŻäťĽĺ é¤ĺ¤ä¸ŞéĺäżĄćŻďźč°ç¨IEmpDAO.doRemoveBatch()ćšćł
     * @param ids ĺĺŤäşĺ¨é¨čŚĺ é¤ć°ćŽçéĺďźć˛Ąćéĺ¤ć°ćŽ
     * @return ĺ é¤ćĺčżĺtrueďźĺŚĺčżĺfalse
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public boolean delete(Set<Integer> ids) throws Exception ;
    /**
     * ć šćŽéĺçźĺˇćĽćžéĺçĺŽć´äżĄćŻďźč°ç¨IEmpDAO.findById()ćšćł
     * @param ids čŚćĽćžçéĺçźĺˇ
     * @return ĺŚććžĺ°äşďźĺĺ°éĺäżĄćŻäťĽVOĺŻščąĄčżĺďźĺŚĺčżĺnull
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public Emp get(int ids) throws Exception ;
    /**
     * ćĽčŻ˘ĺ¨é¨éĺäżĄćŻďźč°ç¨IEmpDAO.findAll()ćšćł
     * @return ćĽčŻ˘çťćäťĽListéĺçĺ˝˘ĺźčżĺďźĺŚćć˛Ąćć°ćŽĺéĺçéżĺşŚä¸?0
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public List<Emp> list() throws Exception ;
    /**
     * ĺŽç°ć°ćŽçć¨ĄçłćĽčŻ˘ä¸ć°ćŽçťčŽĄďźčŚč°ç¨IEmpDAOćĽĺŁçä¸¤ä¸Şćšćłďź<br>
     * <li>č°ç¨IEmpDAO.findAllSplit()ćšćłďźćĽčŻ˘ććçčĄ¨ć°ćŽďźčżĺçćŻList<Emp>ďź?</li>
     * <li>č°ç¨IEmpDAO.getAllCount()ćšćłďźćĽčŻ˘ććçć°ćŽéďźčżĺçćŻIntegerďź?</li>
     * @param currentPage ĺ˝ĺćĺ¨éĄľ
     * @param lineSize ćŻéĄľćžç¤şçčŽ°ĺ˝ć°
     * @param column ć¨ĄçłćĽčŻ˘çć°ćŽĺ
     * @param keyWord ć¨ĄçłćĽčŻ˘ĺłéŽĺ­?
     * @return ćŹćšćłçąäşéčŚčżĺĺ¤ç§ć°ćŽçąťĺďźćäťĽä˝żç¨Mapéĺčżĺďźçąäşçąťĺä¸çťä¸ďźćäťĽććvalueççąťĺčŽžç˝Žä¸şObjectďźčżĺĺĺŽšĺŚä¸ă?<br>
     * <li>key = allEmpsďźvalue = IEmpDAO.findAllSplit()čżĺçťćďźList<Emp>çąťĺďź?</li>
     * <li>key = empCountďźvalue = IEmpDAO.getAllCount()čżĺçťćďźIntegerçąťĺďź?</li>
     * @throws Exception SQLć§čĄĺźĺ¸¸
     */
    public Map<String, Object> list(int currentPage, int lineSize, String column, String keyWord) throws Exception;
}

```

### čäž15-7ďźĺŽäšEmpServiceImplĺ­çąť

```java
package com.yootk.service.impl;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import com.yootk.dbc.DatabaseConnection;
import com.yootk.factory.DAOFactory;
import com.yootk.service.IEmpService;
import com.yootk.vo.Emp;
public class EmpServiceImpl implements IEmpService {
    // ĺ¨čżä¸ŞçąťçĺŻščąĄĺé¨ćäžäşä¸ä¸Şć°ćŽĺşčżćĽçąťçĺŽäžĺĺŻščą?
    private DatabaseConnection dbc = new DatabaseConnection();
    @Override
    public boolean insert(Emp vo) throws Exception {
        try {
            // čŚĺ˘ĺ çéĺçźĺˇĺŚćä¸ĺ­ĺ¨ďźĺfindById()čżĺççťćĺ°ąćŻnull
            // nullčĄ¨ç¤şĺŻäťĽäżĺ­ć°ĺ˘éĺć°ćŽ
            if (DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                     .findById(vo.getEmpno()) == null) {
            // ç´ćĽčżĺIEmpDAO.doCreate()ćšćłçĺ¤ççťć?
               return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doCreate(vo);
            }
            return false;					// ĺ˘ĺ ĺ¤ąč´Ľ
        } catch (Exception e) {
            throw e;						// ćĺźĺ¸¸äş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç?
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
    @Override
    public boolean update(Emp vo) throws Exception {
        try {// ć´ć°ćä˝ĺ°ć šćŽidčżčĄĺ¨é¨ć´ć°ďźć­¤ĺ¤ĺ°ç´ćĽčżĺć°ćŽĺąĺ¤ççťć?
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doUpdate(vo);
        } catch (Exception e) {
            throw e;						// ĺŚććĺźĺ¸¸ďźäş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
    @Override
    public boolean delete(Set<Integer> ids) throws Exception {
        try {
            if (ids == null || ids.size() == 0) {	// ć˛ĄćčŚĺ é¤çć°ćŽ
               return false ;				// ç´ćĽčżĺfalse
            }
            // ĺŚćć­¤ćśéĺĺĺŽšä¸ä¸şçŠşďźĺč°ç¨ć°ćŽĺąĺŽç°ć°ćŽĺ é¤ĺ¤ç
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).doRemoveBatch(ids);
        } catch (Exception e) {
            throw e;						// ĺŚććĺźĺ¸¸ďźäş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
    @Override
    public Emp get(int ids) throws Exception {
        try {
            // ç´ćĽč°ç¨ć°ćŽĺąčżĺćĺŽidçć°ć?
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findById(ids);
        } catch (Exception e) {
            throw e;						// ĺŚććĺźĺ¸¸ďźäş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
    @Override
    public List<Emp> list() throws Exception {
        try {
            // ç´ćĽč°ç¨ć°ćŽĺąčżĺempčĄ¨çĺ¨é¨čŽ°ĺ˝
            return DAOFactory.getIEmpDAOInstance(this.dbc.getConnection()).findAll();
        } catch (Exception e) {
            throw e;						// ĺŚććĺźĺ¸¸ďźäş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
    @Override
    public Map<String, Object> list(int currentPage, int lineSize, String column, 
        String keyWord)  throws Exception {
        try {
            // çąäşć­¤ćšćłéčŚčżĺĺ¤ç§çąťĺçć°ćŽďźćäťĽä˝żç¨Mapéĺäżĺ­čżĺć°ćŽ
            Map<String, Object> map = new HashMap<String, Object>();
            // ĺéĄľćĽčŻ˘ĺşempčĄ¨ä¸­çé¨ĺć°ćŽĺĺŽ?
            map.put("allEmps", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .findAllSplit(currentPage, lineSize, column, keyWord));
            // çťčŽĄĺşempčĄ¨ä¸­çć°ćŽé
            map.put("empCount", DAOFactory.getIEmpDAOInstance(this.dbc.getConnection())
                 .getAllCount(column, keyWord));
            return map; 
        } catch (Exception e) {
            throw e;						// ĺŚććĺźĺ¸¸ďźäş¤çťč˘Ťč°ç¨ĺ¤čżčĄĺ¤ç
        } finally {
            this.dbc.close();				// ä¸çŽĄć°ćŽĺąćä˝ćŻĺŚćĺźĺ¸¸ďźä¸ĺŽčŚĺłé­ć°ćŽĺşčżć?
        }
    }
}

```

### čäž15-8ďźĺŽäšServiceFactory

```java
package com.yootk.factory;
import com.yootk.service.IEmpService;
import com.yootk.service.impl.EmpServiceImpl;
public class ServiceFactory {
    /**
     * ĺĺžIEmpServicećĽĺŁĺŻščąĄ
     * @return IEmpServicećĽĺŁçĺŽäžĺĺŻščąĄ
     */
    public static IEmpService getIEmpServiceInstance() {
        return new EmpServiceImpl();
    }
}

```
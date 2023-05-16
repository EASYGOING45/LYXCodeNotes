# SQL语法

## 常见语法

- SELECT：用于从数据库中选择指定字段的数据。
  - 例子：`SELECT * FROM TableName; (查询表中所有数据)`
- INSERT INTO：用于向指定表中插入新数据。
  - 例子：`INSERT INTO TableName (column1, column2, column3) VALUES (value1, value2, value3); (向表中插入一行新数据)`
- UPDATE：用于更新已有的数据。
  - 例子：UPDATE TableName SET column1 = value1, column2 = value2 WHERE condition; (更新符合条件的行的列值)
- DELETE：用于从指定表中删除符合条件的数据。
  - 例子：`DELETE FROM TableName WHERE condition; (删除符合条件的行)`
- CREATE DATABASE：用于创建新的数据库。
  - 例子：`CREATE DATABASE dbname; (创建名为dbname的新数据库)`
- CREATE TABLE：用于创建新的表。
  - 例子：CREATE TABLE TableName (column1 datatype, column2 datatype, column3 datatype,...); (创建列名为column1,column2,column3...的表)
- ALTER TABLE：用于修改现有表的结构。
  - 例子：`ALTER TABLE TableName ADD column datatype; (向表中添加一个新列column)`
- DROP DATABASE：用于删除数据库。
  - 例子：`DROP DATABASE dbname; (删除名为dbname的数据库)`
- DROP TABLE：用于删除表。
  - 例子：`DROP TABLE TableName; (删除名为TableName的表)`

## 操纵数据（元组）

- SELECT：从一个或多个表中检索数据。
  - 例子：`SELECT * FROM TableName; (获取表中的所有数据)`
- INSERT INTO：向指定表中插入行或数据。
  - 例子：`INSERT INTO TableName (column1, column2, column3) VALUES (value1, value2, value3); (向表中插入新数据)`
- UPDATE：修改数据，也可用于更新表中现有的行。
  - 例子：`UPDATE TableName SET column1 = value1 WHERE column2 = value2; (更新表中符合条件的列)`
- DELETE：从指定表中删除行。
  - 例子：`DELETE FROM TableName WHERE column = value; (删除符合条件的行)`
- ORDER BY：按照列中的值对结果进行排序。
  - 例子：`SELECT column1, column2 FROM TableName ORDER BY column1 ASC; (按升序排列结果)`
- GROUP BY：将结果分成组，并将聚合函数应用于每个组。
  - 例子：`SELECT column1, COUNT(column1) FROM TableName GROUP BY column1; (基于 column1 分组并计算每个组中的列数)`
- JOIN：将两个或多个表的行组合在一起，以便与另一个表中的行进行匹配。
  - 例子：`SELECT column1, column2 FROM table1 JOIN table2 ON table1.column = table2.column; (将两个表连接到具有相同数据的列上)`
- AVG：计算选择的列的平均值。
  - 例子：`SELECT AVG(column1) FROM TableName; (计算表中 column1 列的平均值)`
- DISTINCT：返回唯一不同的值。
  - 例子：`SELECT DISTINCT column1 FROM TableName; (获取表中 column1 列的唯一不同的值)`
- COUNT：计算列中行的数量。
  - 例子：`SELECT COUNT(column1) FROM TableName; (计算表中 column1 列的行数)`
- MAX：返回选择列的最大值。
  - 例子：`SELECT MAX(column1) FROM TableName; (获取表中 column1 列的最大值)`
- MIN：返回选择列的最小值。
  - 例子：`SELECT MIN(column1) FROM TableName; (获取表中 column1 列的最小值)`
- LIKE：用于执行模式匹配搜索。
  - 例子：`SELECT column1 FROM TableName WHERE column1 LIKE 'a%'; (获取表中 column1 列以 'a' 字母开头的数据)`
- IN：用于指定条件范围。
  - 例子：`SELECT column1 FROM TableName WHERE column1 IN ('value1', 'value2'); (获取表中 column1 列包含 value1 或 value2 的数据)`

## 操纵数据表

### 创建表

- #### 使用CREATE TABLE语句

- CREATE TABLE语句是创建和定义关系型数据库表的最常用方法。

  例如，下面的SQL语句将创建名为“employees”的新表：

  ```c++
  CREATE TABLE employees (
  emp_id INT NOT NULL,
  first_name VARCHAR(50),
  last_name VARCHAR(50),
  email VARCHAR(50),
  hire_date DATE,
  PRIMARY KEY(emp_id)
  );
  ```

- #### 使用SELECT INTO语句

- SELECT INTO语句是创建新表的另一种方式。该语句创建一个新表，并从现有表或视图中选择数据。

  例如，下面的SQL语句将创建名为“new_employees”的新表，并从“employees”表中选择一部分列：

  `SELECT emp_id, first_name, last_name INTO new_employees`
  `FROM employees;`

- #### 复制现有表

- 用户可以通过复制现有表的方式来创建新表。这个方法主要适用于需要从当前表进行大量修改或对表结构进行细微调整的情形。

- 例如，以下SQL语句将复制现有表“employees”中的所有数据并创建新表“new_employees”：

  `CREATE TABLE new_employees AS`
  `SELECT * FROM employees;`

### 删除表

#### 使用DROP TABLE语句

最常用的删除表方法是使用DROP TABLE语句。该语句从数据库中永久删除指定的表。语法如下：

`DROP TABLE table_name;`

例如，以下SQL语句将永久删除名为“employees”的表：

`DROP TABLE employees;`

#### 使用TRUNCATE TABLE语句

TRUNCATE TABLE语句在删除表之前删除表中的所有数据，但将表结构保留下来。该语句比DROP TABLE语句快，特别是在删除大型表时，因为它不会保留任何日志信息，也不会检查约束。语法如下：

`TRUNCATE TABLE table_name;`

例如，以下SQL语句将删除名为“employees”的表中的所有数据：

`TRUNCATE TABLE employees;`
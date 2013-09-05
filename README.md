# 软件工程
使用Qt4编写的一个小Demo: *企业人事管理系统*

## 依赖 Dependencies
* libqt4-gui libqt4-core
* mysql-server 
* libqt4-sql-mysql

### Optional
* PHP 5.2.0(or newer) phpMyAdmin

## 截图 Screenshot

![截图](https://github.com/xuefu/EnterprisePersonnelManagementSystem/blob/master/images/workers.jpg)

## 安装方法 Install Instructions

在Ubuntu 12.04 x86上测试通过

### 数据库 MySQL

 建数据库前，须对数据库进行相关配置, 对root用户设置密码为: xtiprfw

 创建数据库EnterprisePersonnelManagementSystem

 数据库恢复, 建议用phpMyAdmin对数据库文件EnterprisePersonnelManagementSystem.sql进行恢复


```
qmake EnterprisePersonnelManagementSystem.pro
make

```
得到`EnterprisePersonnelManagementSystem`后直接运行即可

## BUGS
* <del>在长时间不断进行界面切换会崩溃</del>
* 在GBK或其它非UTF-8编码下会乱码

## LICENSE
本项目基于MIT协议发布

MIT: [http://rem.mit-license.org](http://rem.mit-license.org)

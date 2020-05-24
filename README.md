# C++ Web Chat Room

## Web connect use socket

## Database use MySQL

## Database connect use `mysql.h`

* Two Friends talk

Database Setting

Database Name : chat

Field:

* FromUserID : unsigned long long
* TargetUserID : unsigned long long
* content : TEXT

create command:

```mysql
CREATE TABLE chat (
	id INT UNSIGNED AUTO_INCREMENT,
  fromUserID INT NOT NULL,
  targetUserID INT NOT NULL,
  content TEXT NOT NULL,
  chatAt TIMESTAMP NOT NULL,
  PRIMARY KEY(id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
```

Insert command:

```mysql
INSERT INTO chat 
(fromUserID, targetUserID, content, chatAt)
VALUES
(1, 2, "1234", NOW());
```

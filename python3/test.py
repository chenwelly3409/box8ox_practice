import pymysql 
conn=pymysql.connect( 
    host='key.cfphm1sjmc3u.ap-northeast-1.rds.amazonaws.com', #本地127.0.0.1
    port=3306, #默認3306埠 
    user='blockfuture', #mysql最高許可權用戶
    passwd='Wallstreetblockfuture', #root用戶密碼
    db='key', #database name
)
 #建立游標 

cur=conn.cursor() #建立一個user表,execute() 執行sql語句 
# cur.execute("create table user1(username varchar(20),password varchar(30))") #插入一條資料 
# cur.execute( "INSERT INTO `history` ( `btc_account`, `action`, `value` ) Values ( '" + s[1] + "' , '" + "earn" + "', '" +str(tmp) + ")";
#查詢 

sqlString = "SELECT * FROM `key`"
key=cur.execute(sqlString) #獲得資料---單條fetchone() 多條fetchmany()
key_info=cur.fetchmany(key) #把資料列印出來

# print(key_info)
# print(info[0][1])

sqlString = "SELECT * FROM `history` where `btc_account`= '" + key_info[0][1] + "'"
history = cur.execute(sqlString)
history_info = cur.fetchmany(history)

print(history_info)


#關閉游標     
cur.close() 
#提交事物 不寫的話資料庫不會改動 
conn.commit() 
#斷開連線 
conn.close()

import pymysql
conn=pymysql.connect(
    
)

def pay(payAmount):
    sum = 0
    cur = conn.cursor()
    a = cur.execute("SELECT * FROM `key`.`key`")
    usr_Balance = cur.fetchmany(a)
    for s in usr_Balance:
            sum += s[3]

    for s in usr_Balance:
        if s[3] > 0:
            tmp = s[3] / sum * payAmount
            sqlString = "INSERT INTO `history` ( `account`, `action`, `value` , `type`) Values ( '" + s[1] + "' , '" + "earn" + "', " + str(tmp) + ", '" + "ETH" + "' )"
            cur.execute(sqlString)
    cur.close()
    conn.commit()
    conn.close()
if __name__ == '__main__':
    sum = 0
    cur = conn.cursor()
    a = cur.execute("SELECT * FROM `key`.`key`")
    usr_Balance = cur.fetchmany(a)
    for s in usr_Balance:
            sum += s[3]
    print(sum)
    x = float(input('Input profit to pay dividend:\n'))
    pay(x)


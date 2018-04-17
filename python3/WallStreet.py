# ###############################
# Auther : Box & Ray
# Time : 2017/8/15 21:01
# Name : WallStreet
################################

import os
import time
import json
from random import *
Account_data = {
    'Sum_USD' : 0.00,
    'total' : {
        'USD' : 0.00,
        'BTC' : 0.00,
        'ETH' : 0.00,
        'ZEC' : 0.00
    },
    'Poloniex' : {
        'USD' : 5142.44,
        'BTC' : 0.88639,
        'ETH' : 0.00,
        'ZEC' : 0.00
    },
    'Bittrex' : {
        'USD' : 5002.34,
        'BTC' : 1.0732,
        'ETH' : 0.00,
        'ZEC' : 0.00
    },
    'Bitfinex' : {
        'USD' : 5062.11,
        'BTC' : 1.11361,
        'ETH' : 0.00,
        'ZEC' : 0.00
    }
}

def fee_switch(name):
    return {
        'Poloniex' : 0.25,
        'Bittrex' : 0.25,
        'Bitfinex' : 0.2,
    }[name]
def btc2usd():
    return 4366
def eth2usd():
    return 302
def zec2usd():
    return 210.38

def print_SumUSD():
    BTC2USD=btc2usd()
    ETH2USD=eth2usd()
    ZEC2USD=zec2usd()
    time.sleep(1)
    print("\n***************************************")
    Account_data['Sum_USD'] = round(Account_data['total']['USD'] + Account_data['total']['BTC'] * BTC2USD + Account_data['total']['ETH'] * ETH2USD + Account_data['total']['ZEC'] * ZEC2USD,8)
    print( ' BTC : USD = 1 : {} | ETH :USD = 1 : {} | ZEC : USD = 1 : {} '.format( btc2usd(), eth2usd(), zec2usd()  ) )
    print(' => 目前總貨幣價值(USD) : \033[7;33;40m{}\033[0m'.format(Account_data['Sum_USD']))

def print_total():
    print("\n***************************************")
    Account_data['total']['USD'] = round(Account_data['Poloniex']['USD'] + Account_data['Bittrex']['USD'] + Account_data['Bitfinex']['USD'],8)
    Account_data['total']['BTC'] = round(Account_data['Poloniex']['BTC'] + Account_data['Bittrex']['BTC'] + Account_data['Bitfinex']['BTC'],8)
    Account_data['total']['ETH'] = round(Account_data['Poloniex']['ETH'] + Account_data['Bittrex']['ETH'] + Account_data['Bitfinex']['ETH'],8)
    Account_data['total']['ZEC'] = round(Account_data['Poloniex']['ZEC'] + Account_data['Bittrex']['ZEC'] + Account_data['Bitfinex']['ZEC'],8)

    print("=> 貨幣總值： USD :　{} | BTC : {} | ETH : {} | ZEC : {} ".format(Account_data['total']['USD'],Account_data['total']['BTC'],Account_data['total']['ETH'],Account_data['total']['ZEC']))

def print_detail():
    print("\n***************************************")
    print('  * Poloniex : USD : 　{} 、 BTC : {} 、 ETH : {} 、 ZEC : {} *'.format(Account_data['Poloniex']['USD'],Account_data['Poloniex']['BTC'],Account_data['Poloniex']['ETH'],Account_data['Poloniex']['ZEC']))
    print('  * Bittrex : USD : {} 、 BTC : {} 、 ETH : {}、 ZEC : {} *'.format(Account_data['Bittrex']['USD'],Account_data['Bittrex']['BTC'],Account_data['Bittrex']['ETH'],Account_data['Bittrex']['ZEC']))
    print('  * Bitfinex : USD : {} 、 BTC : {} 、 ETH : {} 、 ZEC : {} *'.format(Account_data['Bitfinex']['USD'],Account_data['Bitfinex']['BTC'],Account_data['Bitfinex']['ETH'],Account_data['Bitfinex']['ZEC']))

def print_Transactions( symbol_1, symbol_2, Trans_1, Trans_2, Sell_num, Buy_num, boo_arbitrage ):
    fee_Sell = round(Sell_num - ( Sell_num * fee_switch(Trans_1)/100 ),8)
    fee_Buy = round(Buy_num + ( Buy_num * fee_switch(Trans_2)/100 ),8)
    pre_Profit = ( Sell_num - Buy_num ) / Buy_num * 100
    last_Profit = ( fee_Sell - fee_Buy ) / fee_Buy * 100

    print("--------------------------------------")
    print('> 最高獲利搬磚 <')
    time.sleep(uniform(20,40)/10) #2秒到4秒不等的等待
    print("--------------------------------------")
    print('=> {}-{}\t[ Sell ] \t \t  \t[ Buy ]'.format(symbol_1, symbol_2))
    if pre_Profit > 0 :
        print(' >>  \033[1;30;47m{}\033[0m\t| {:.8f}\t| \033[1;30;47m{}\033[0m\t| {:.8f} \t| \033[7;32;40m{} %\033[0m'.format(Trans_1, Sell_num, Trans_2, Buy_num, pre_Profit))
    else:
        print(' >>  \033[1;30;47m{}\033[0m\t| {:.8f}\t| \033[1;30;47m{}\033[0m\t| {:.8f} \t| \033[7;31;40m{} %\033[0m'.format(Trans_1, Sell_num, Trans_2, Buy_num, pre_Profit))
    if last_Profit > 0.1 : #實際收益超過0.1%才給予綠色推薦搬磚
        print(' >> {}\t| {:.8f}\t| {}\t| {:.8f} \t| \033[7;32;40m{} %\033[0m'.format('fee ' + str(fee_switch(Trans_1)), fee_Sell, 'fee '+ str(fee_switch(Trans_2)), fee_Buy, last_Profit))
    else :
        if last_Profit > 0 : # 0~0.1之間的給予紫色 不推薦搬磚因為獲利太少
             print(' >> {}\t| {:.8f}\t| {}\t| {:.8f} \t| \033[7;35;40m{} %\033[0m'.format('fee ' + str(fee_switch(Trans_1)), fee_Sell, 'fee '+ str(fee_switch(Trans_2)), fee_Buy, last_Profit))
        else :
             print(' >> {}\t| {:.8f}\t| {}\t| {:.8f} \t| \033[7;31;40m{} %\033[0m'.format('fee ' + str(fee_switch(Trans_1)), fee_Sell, 'fee '+ str(fee_switch(Trans_2)), fee_Buy, last_Profit))
    if boo_arbitrage :
        time.sleep(0.75)
        print_arbitrage( symbol_1, symbol_2, Trans_1, Trans_2, fee_Sell, fee_Buy )

def print_arbitrage(symbol_1, symbol_2, Trans_1, Trans_2, fee_Sell, fee_Buy):
    print('======================================')
    time.sleep(1)
    print(' => \033[1;30;43m發現有利潤可套利搬磚程序，程序開始進行\033[0m')
    time.sleep(1)
    arbitrage = ' >>> 套利進行中 .'
    for i in range(0,15):
        print(arbitrage, end="\r")
        time.sleep(0.8)
        arbitrage += '.'
    print(arbitrage+'\n\033[7;33;40mSucces!!\033[0m')

    Amount = 0.37 #套利的金額

    Account_data[Trans_1][symbol_1] += fee_Sell * Amount
    Account_data[Trans_1][symbol_2] -= Amount
    Account_data[Trans_2][symbol_1] -= fee_Buy * Amount
    Account_data[Trans_2][symbol_2] += Amount
    
    time.sleep(3)
    print_detail()
    time.sleep(1)
    print_total()
    time.sleep(2)
    print(' => 搬磚套利成功，本次套利{}顆{} 共獲得 : \033[7;32;40m{} {}\033[0m'.format(Amount,symbol_2,round(fee_Sell * Amount-fee_Buy * Amount,8), symbol_1) )
   
    # time.sleep(1)
    print_SumUSD()

def main():
    print('歡迎使用\033[1;31;40m「WallStreet」\033[0m，此版本為v_1.0.0.2，請確認程式為最新版本\n')
    print('***此程式目前還在測試階段***')
    
    update = '=> 檢查更新 .'
    for i in range(0,2):
        print(update, end="\r")
        time.sleep(1)
        update += '.'
    print(update+'\nDone.')
    
    System_init = '=> 系統初始化 .'
    for i in range(0,5):
        print(System_init, end="\r")
        time.sleep(1)
        System_init += '.'
    print(System_init+'\nDone.')
    
    Account_init = '=> 帳戶連結中 .'
    for i in range(0,8):
        print(Account_init, end="\r")
        time.sleep(1)
        Account_init += '.'
    print(Account_init+'\nDone.')
    
    print("***************************************")
    print("=> \033[1;31;40m「WallStreet」\033[0m_v1.0.0.2_歡迎使用 - 歡迎回報與提供意見")
    time.sleep(3)
    print_detail()
    time.sleep(1)
    print_total()
    # time.sleep(1)
    print_SumUSD()
    time.sleep(1)

    print("\n*********自動搬磚模式分析開始*************")
    time.sleep(2)
    
    print_Transactions('USD', 'BTC','Bitfinex','Bitfinex',4280.1,4280.4, False)
    print_Transactions('USD', 'BTC','Bitfinex','Poloniex',4280,4274.99999, False)
    print_Transactions('USD', 'BTC','Bitfinex','Poloniex',4279.1,4271.76518351, False)
    print_Transactions('USD', 'BTC','Bittrex','Bitfinex',4295,4279.9, False)
    print_Transactions('USD', 'BTC','Bitfinex','Poloniex',4289,4281.99999, False)
    print_Transactions('USD', 'BTC','Bitfinex','Poloniex',4285.3,4282, False)
    print_Transactions('USD', 'BTC','Bitfinex','Poloniex',4285.5,4281.999998, False)
    print_Transactions('USD', 'BTC','Bitfinex','Bittrex',4282.8,4280, False)
    print_Transactions('USD', 'BTC','Bitfinex','Bittrex',4287.3,4270, False)
    print_Transactions('USD', 'BTC','Poloniex','Bitfinex',4288,4265.4431, False)
    print_Transactions('USD', 'BTC','Bitfinex','Bittrex',4282.2,4270, False)
    print_Transactions('USD', 'BTC','Bitfinex','Bittrex',4282.6,4275, False)
    print_Transactions('USD', 'BTC','Bitfinex','Bittrex',4283.1,4275, False)
    print_Transactions('USD', 'BTC','Poloniex','Bitfinex',4288,4263.4431, True)

    # print(Account_data)
    
    print("***************************************")



main()
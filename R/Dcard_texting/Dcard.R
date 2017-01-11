library(jsonlite)

Crawler <- function() {
	url = "https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false&before=" #文章看板

	Dcard <<-fromJSON("https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false")

	for( i in c( 1 : 1499 ) ) {  #爬幾頁
		id = Dcard[30*i,1];
		temp_url = paste( url, id, sep = "" );
		Dcard <<- rbind( Dcard, fromJSON(temp_url) );
		
	}

}


Crawler();
#爬資料

data <- Dcard

data[,4:8] = NULL
data[,5] = NULL
data[,7:10] = NULL
data[,9:13] = NULL

#刪除一些不必要的欄位

summary(as.matrix(data))
#簡單看一下資料

school <- function() {
	school <- as.matrix(data[,8])
	sum_sch <- summary(school, max=11)
	school_name <- c()
	school_num <- c()

	for( i in c(1:10) ) {
		school_name <- c( school_name, strsplit(gsub(" ",replacement="",sum_sch[i]),split=":", fixed = T )[[1]][1] )
		school_num <- c( school_num, as.numeric( strsplit(gsub(" ",replacement="",sum_sch[i]),split=":", fixed = T )[[1]][2] ) )

		#school_name <- c( school_name, strsplit(sum_sch[i],split=" ", fixed = T )[[1]][1] )
		#school_num <- c( school_num, as.numeric( strsplit( sum_sch[i],split=" ", fixed = T )[[1]][6] ) )
	}


	school_sum_data <<- data.frame(school_name,school_num)

} #統計學校

Sex <- function() {
	Sex <- summary( as.matrix(data[,7]) );
	Sex2 <- c("Male","Female");
	num <- c(
		as.numeric( strsplit( Sex[2],split=":", fixed = T )[[1]][2] ),
		as.numeric( strsplit( Sex[3],split=":", fixed = T )[[1]][2] )
		)

	Sex_data <<- data.frame(Sex2,num);
} #統計性別

library("jiebaR")

Sys.setlocale(category = "LC_ALL", locale = "cht")
cc = worker()

cc[text]

title_token <- function() {

	token <<- c()

	for( i in c(1:45000) ) {
		if( data[i,2]!= "." )
		token <<- c( token, cc[data[i,2]] )
	}

} #將文章資料抓出來切出token

title_token();
token2 <- token[nchar(token[])>1]

token_table <- function() {
	temp <- summary(as.matrix(token2),max=301)
	t_name <- c();
	t_fre <- c();
	
	for( i in c(1:300) ) {
		t_name <- c( t_name, strsplit(gsub(" ",replacement="",temp[i]),split=":", fixed = T )[[1]][1] )
		t_fre <- c( t_fre, as.numeric( strsplit(gsub(" ",replacement="",temp[i]),split=":", fixed = T )[[1]][2] ) )
	}

	token_table <<- data.frame(t_name,t_fre);

} #切出所有大於1的token

token_table();

library(wordcloud2)  #文字雲套件
wordcloud2(token_table, color = "random-light", backgroundColor = "black")

time <- function() {
	time <- data[,4]
	temp <- c()

	for( i in c(1:45000) ) {
		temp <- c( temp, strsplit(time[i],split="T", fixed = T )[[1]][2] )
	}

	time_data <<- c()

	for( i in c(1:45000) ) {
		time_data <<- c( time_data, strsplit(temp[i],split=":", fixed = T )[[1]][1] )
	}

	time2();

}  #取出所有時間的小時部分

time2 <- function() {
	temp <<- summary( as.matrix(time_data), max = 24 );
	hour <- c();
	hour_count <- c();

	for( i in c(1:24) ) {
		hour <- c( hour, strsplit(gsub(" ",replacement="",temp[i]),split=":", fixed = T )[[1]][1] )
		hour_count <- c( hour_count, as.numeric( strsplit(gsub(" ",replacement="",temp[i]),split=":", fixed = T )[[1]][2] ) )
	}

	time_data <<- data.frame(hour, hour_count);

} #小時分類

###下面沒有用到###


Dcard = as.matrix(Dcard)
#轉入矩陣

write.table(Dcard, file = "Dcard.CSV", sep = "," )
#輸出csv檔案

#有問題歡迎詢問
#此程式碼是以廢文版當範例

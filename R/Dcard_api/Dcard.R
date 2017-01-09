library(jsonlite)

Crawler <- function() {
	url = "https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false&before=" #文章看板

	Dcard <<-fromJSON("https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false")

	for( i in c( 1 : 3 ) ) {  #爬幾頁
		id = Dcard[30,1];
		temp_url = paste( url, id, sep = "" );
		Dcard <<- rbind( Dcard, fromJSON(temp_url) );
		
	}

}


Crawler();

Dcard = as.matrix(Dcard)
#轉入矩陣

write.table(Dcard, file = "Dcard.CSV", sep = "," )
#輸出csv檔案

#有問題歡迎詢問
#此程式碼是以廢文版當範例

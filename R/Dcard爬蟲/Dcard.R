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

write.table(Dcard, file = "Dcard.CSV", sep = "," )

#有問題歡迎來問

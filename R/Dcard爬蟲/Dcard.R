library(jsonlite)

Crawler <- function() {
	url = "https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false&before="

	Dcard <<-fromJSON("https://www.dcard.tw/_api/forums/whysoserious/posts?popular=false")

	for( i in c( 1 : 1500 ) ) {
		id = Dcard[30,1];
		temp_url = paste( url, id, sep = "" );
		Dcard <<- rbind( Dcard, fromJSON(temp_url) );
		
	}

}

Crawler();

Dcard = as.matrix(Dcard)

write.table(Dcard, file = "Dcard.CSV", sep = "," )



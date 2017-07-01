function sum( i ) {
    if( i > 0 ) {
        return i * sum( i-1 );
        
    }
    else{
        return 1;
    }
}

console.log(sum(10));

sum = 1 ;

for (var i = 1 ; i < 11 ; i++ ) {
    sum = sum * i ;
}

console.log(sum);

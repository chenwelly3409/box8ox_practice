function Square( num ) {
    for( var i = 0 ; i < num ; i++ ) {
        if( i*i == num ) {
            return i;
        }
    }
    return null;
}

console.log("+-"+Square(30));

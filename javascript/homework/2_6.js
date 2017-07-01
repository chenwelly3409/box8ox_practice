function GCD ( num1, num2 ) {
    for ( var i = num1 ; i > 1 ; i-- ) {
        if( num1 % i == 0 && num2 % i == 0 )
            return i;
    }
    return false;
}

console.log(GCD(12,20));
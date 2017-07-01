function degree( num ) {
    if ( num >= 90 )
        return 'A';
    if ( num >= 80 && num < 90 )
        return 'B';
    if ( num >= 70 && num < 80 )
        return 'C';
    else
        return 'D';

}

console.log(degree(69));
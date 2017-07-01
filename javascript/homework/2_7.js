function binary( num ) {
    var ans = "";

    for ( var i = num ; num >= 2 ; ) {
        if( num % 2 == 0 ) {
            ans = str(0,ans);
            num = num/2;
        }
        else if ( num % 2 == 1) {
            ans = str(1,ans);
            num = (num-1)/2;
        }
    }

    if( num == 1 ) {
        ans = str(1,ans);
    }
    if( num == 0 ) {
        ans = str(0,ans);
    }

    return ans;
}

function str( A, B ) {
    return A+B+"";
}


for( var i = 0 ; i < 100 ; i ++ ) {
    console.log(binary(i));
}

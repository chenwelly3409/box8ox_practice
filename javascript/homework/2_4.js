function m3( num ) {
    if( num % 3 == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

function m5( num ) {
    if( num % 5 == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

function m7( num ) {
    if( num % 7 == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

function m357( num1, num2 ) {
    for( var i = num1 ; i <= num2 ; i++ ) {
        if( m3(i) || m5(i) || m7(i) ) 
            console.log(i+", ");
    }
}

m357(10,15);
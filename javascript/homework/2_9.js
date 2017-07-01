function isPrime( num ) {
    for ( var i = 2 ; i < num ; i++ ) {
        if( num%i == 0 )
            return false;
    }

    return true;
}

function countPrime( num1, num2 ) {
    var ans = 0;
    for ( var i = num1 ; i <= num2 ; i++ ) {
        if( isPrime(i) ) {
            ans++;
        }
    }
    return ans;
}

console.log(countPrime(3,7));

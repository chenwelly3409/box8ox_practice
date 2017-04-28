var dict = { name : "Box", age : 23 };

dict["email"] = "chenwelly3409@gmail.com";
dict.tel = "0988304377";

for( var key in dict ) {
    console.log( "Key = ", key, " value = ", dict[key] );
}

console.log("age = ", dict.age);
console.log("birthday = ", dict.birthday);
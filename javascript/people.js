var people = {
    name: "Box",
    age: 23,
    print: function() {
        console.log( "name = ", this.name, " age = ", this.age );
    }
}

people.print();
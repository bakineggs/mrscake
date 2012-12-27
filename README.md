About:
------

mrscake (read: "Mrs. Cake") is a machine learning library that automatically picks the best model for you.
It can also generate code. 
Generated code might look like this:

```python

def predict(aquatic, domestic, eggs, backbone, feathers, 
            predator, airborne, hair, toothed, tail, 
            breathes, catsize, venomous, legs, fins, milk):
    if eggs == "no":
        return "mammal"
    else:
        if backbone == "yes":
            return "bird"
        else:
            if aquatic == "no":
                return "insect"
            else:
                return "crustacean"
```


Compiling:
----------

Compile it using
    ./configure
    make
    make install
.

It has a Ruby and a Python interface.

Usage (Python):
---------------

import mrscake
data = mrscake.DataSet()
data.add(["a", 1.0, "blue"], output="yes")
data.add(["a", 3.0, "red"], output="yes")
data.add(["b", 2.0, "red"], output="no")
data.add(["b", 3.0, "blue"], output="no")
data.add(["a", 5.0, "blue"], output="yes")
data.add(["b", 4.0, "blue"], output="yes")
model = data.train()

result = model.predict(["a", 2.0, "red"])

code = model.generate_code("python") # or: ruby, javascript, c

print code

Usage (Ruby):
-------------

require 'mrscake'
data = MrsCake::DataSet.new
data.add([:a, 1.0, :blue], :yes)
data.add([:a, 3.0, :red], :yes)
data.add([:b, 2.0, :red], :no)
data.add([:b, 3.0, :blue], :no)
data.add([:a, 5.0, :blue], :yes)
data.add([:b, 4.0, :blue], :yes)
model = data.train()
model.print

result = model.predict([:a, 2.0, :red])

code = model.generate_code("ruby") # or: ruby, javascript, c

puts code
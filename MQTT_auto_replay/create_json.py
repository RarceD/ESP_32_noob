import json 
from not_show import *

# convert into JSON:
y = json.dumps(DEVISE_TO_ASK, indent = 4)

# the result is a JSON string:
print(y)
import sys
if( len( sys.argv ) < 2 ):
    print("Put the input text as a CLI argument pls")
    sys.exit(1)
text = sys.argv[1]
print("".join(["'"+x+"', " for x in text]))

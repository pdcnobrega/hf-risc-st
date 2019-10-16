TEST_ROOT=$(pwd)

echo "Running tests at \"$TEST_ROOT\""

for dir in */ ; do
        echo About to test \"$dir\" at \"$TEST_ROOT/$dir\"

        if [ ! -f $TEST_ROOT/$dir/test.c ]; then
                echo "Warning: Missing test source (test.c) for \"$dir\""
                continue
        fi;
        if [ ! -f $TEST_ROOT/$dir/makefile ]; then
                echo "Warning: Missing makefile (makefile) for \"$dir\""
                continue
        fi;

        cd "$TEST_ROOT/$dir"
        time make test
        status=$?
        if [ $status -ne 0 ]; then
                echo "Test failed for \"$dir\""
                exit $status
        fi;
done
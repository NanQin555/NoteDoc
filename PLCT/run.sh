USER="spacemit"
REMOTE_IP="211.83.110.5"

REMOTE_PATH="/home/spacemit/opencv"
OPENCV_PATH="/home/nanqin/project/opencv"
LOCAL_PATH="/home/nanqin/project/opencv/build/bin"
PLCT="/home/nanqin/NoteDoc/PLCT"
summary="/home/nanqin/project/opencv/modules/ts/misc/summary.py"

TEST="imgproc"
TEST_FILTER="--gtest_filter=\"*WarpAffine*\""
PERF_FILTER="--gtest_filter=\"*WarpAffine*\""

build=false
upload=false
run_test=false
run_perf=false

while getopts ":btpu" opt; do
    case ${opt} in
        b )
            build=true
            ;;
        t )
            run_test=true
            ;;
        p )
            run_perf=true
            ;;
        u )
            upload=true
            ;;
        \? )
            each "Invalid option: -$OPTARG" 1>&2
            exit 1
            ;;
    esac
done
shift $((OPTIND -1))

if [ "$build" = true ]; then
    cd ${OPENCV_PATH}/build
    ninja -j $(nproc)
fi 

if [ "$upload" = true ]; then
    scp ${LOCAL_PATH}/opencv_test_core ${LOCAL_PATH}/opencv_perf_${TEST} ${USER}@${REMOTE_IP}:${REMOTE_PATH}
fi

if [ "$run_test" = true ]; then
    ssh ${USER}@${REMOTE_IP} "${REMOTE_PATH}/opencv_test_${TEST} ${TEST_FILTER}" 
fi

if [ "$run_perf" = true ]; then
    ssh ${USER}@${REMOTE_IP} "${REMOTE_PATH}/opencv_perf_${TEST} ${PERF_FILTER} --gtest_output=xml:${REMOTE_PATH}/result.xml"
    scp ${USER}@${REMOTE_IP}:${REMOTE_PATH}/result.xml ${PLCT}/xml
    ${summary} ${PLCT}/xml/original.xml ${PLCT}/xml/result.xml
fi

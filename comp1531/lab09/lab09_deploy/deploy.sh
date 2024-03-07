WORKING_DIRECTORY="~/www/lab09_deploy"

USERNAME="weizhe-diao"
SSH_HOST="ssh-weizhe-diao.alwaysdata.net"

rm -rf ./**/__pycache__ ./**/.pytest_cache > /dev/null
scp -r ./* "$USERNAME@$SSH_HOST:$WORKING_DIRECTORY"
ssh "$USERNAME@$SSH_HOST" "cd $WORKING_DIRECTORY && source env/bin/activate && pip3 install -r requirements.txt"

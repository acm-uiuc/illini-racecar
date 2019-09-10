# illini-racecar

Base repo for the illini-racecar robotics platform.

## Running ROS in docker with no GUI
```
docker pull illiniracecar/illini-racecar-base:latest
docker run -it illiniracecar/illini-racecar-base:latest
```

## Running ROS in docker with GUI
```
docker pull illiniracecar/illini-racecar-base:latest
docker run -it \
    --user=$USER \
    --env="DISPLAY" \
    --workdir="/home/$USER" \
    --volume="/home/$USER:/home/$USER" \
    --volume="/etc/group:/etc/group:ro" \
    --volume="/etc/passwd:/etc/passwd:ro" \
    --volume="/etc/shadow:/etc/shadow:ro" \
    --volume="/etc/sudoers.d:/etc/sudoers.d:ro" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    illiniracecar/illini-racecar-base:latest
```

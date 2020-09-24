typedef FILE Sensor;

Sensor* openSensor(char* path) {
    return fopen(path, "r");
}

int readSensor(Sensor* sensor, int* data) {
    return fscanf(sensor, "%d", data);
}

-- Connessione al database
\connect dbname=logdb_smarthome user=postgres password=12345 host=localhost port=5432

-- Creazione della tabella Light
CREATE TABLE IF NOT EXISTS Light (
    id SERIAL,
    state VARCHAR(20) NOT NULL,
    color VARCHAR(20) NOT NULL,
    intensity INT NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

-- Creazione della tabella Camera
CREATE TABLE IF NOT EXISTS Camera (
    id SERIAL,
    state VARCHAR(20) NOT NULL,
    recording BOOLEAN NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

-- Creazione della tabella Conditioner
CREATE TABLE IF NOT EXISTS Conditioner (
    id SERIAL,
    state VARCHAR(20) NOT NULL,
    temperature INT NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

-- Creazione della tabella Device
CREATE TABLE IF NOT EXISTS Device (
    id SERIAL,
    state VARCHAR(20) NOT NULL,
    name VARCHAR(20) NOT NULL,
    start INT NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

-- Creazione della tabella Sensor
CREATE TABLE IF NOT EXISTS Sensor (
    id SERIAL,
    state VARCHAR(15) NOT NULL,
    checking BOOLEAN NOT NULL,
    movement BOOLEAN NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

-- Creazione della tabella SensorGarden
CREATE TABLE IF NOT EXISTS SensorGarden (
    id SERIAL,
    state VARCHAR(15) NOT NULL,
    temperature INT NOT NULL,
    humidity INT NOT NULL,
    pid INT NOT NULL,
    nanosec BIGINT NOT NULL,
    PRIMARY KEY (nanosec, id),
);

CREATE TABLE IF NOT EXISTS LogActivity (
    name_activity varchar(20)NOT NULL,
    nanosec BIGINT NOT NULL,
    pid INT NOT NULL,
    PRIMARY KEY (name_activity, nanosec),
)

CREATE TABLE IF NOT EXISTS SecurityRecap (
    nanosec BIGINT NOT NULL,
    pid INT NOT NULL,
    PRIMARY KEY (nanosec),

)

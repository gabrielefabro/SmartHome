-- database already exists
\ c :dbname -- Pick the one most appropriate for your application

CREATE TABLE IF NOT EXISTS Light (
        id int,
        state VARCHAR(20) NOT NULL,
        color VARCHAR(20) NOT NULL,
        intensity int NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
) CREATE TABLE IF NOT EXISTS Camera (
        id int,
        state VARCHAR(20) NOT NULL,
        recording boolean NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
) CREATE TABLE IF NOT EXISTS Conditioner (
        id int,
        state VARCHAR(20) NOT NULL,
        temperature int NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
) CREATE TABLE IF NOT EXISTS Device (
        id int,
        state VARCHAR(20) NOT NULL,
        name VARCHAR(20) NOT NULL,
        start int NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
) CREATE TABLE IF NOT EXISTS Sensor (
        id int,
        state VARCHAR(15) NOT NULL,
        checking boolean NOT NULL movement boolean NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
) CREATE TABLE IF NOT EXISTS SensorGarden (
        id int NOT NULL,
        state VARCHAR(15) NOT NULL,
        temperature int NOT NULL,
        humidity int NOT NULL,
        pid int NOT NULL,
        nanosec bigint NOT NULL,
        PRIMARY KEY (nanosec, id),
        CONSTRAINT id_ref FOREIGN KEY(id) REFERENCES TimeVar(id)
)
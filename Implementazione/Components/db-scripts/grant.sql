
\c :dbname postgres

-- user already exists
GRANT ALL PRIVILEGES ON DATABASE :dbname to :username ;


ALTER TABLE Light OWNER TO :username ;
ALTER TABLE Camera OWNER TO :username ;
ALTER TABLE Device OWNER TO :username ;
ALTER TABLE Conditioner OWNER TO :username ;
ALTER TABLE Sensor OWNER TO :username ;
ALTER TABLE SensorGarden OWNER TO :username ;

-- grant all privileges on all tables in schema public to :username ;
-- grant all privileges on all sequences in schema public to :username ;

GRANT ALL ON SCHEMA public TO :username ;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO :username ;

CREATE TABLE blob_merge_table (
	benchmark VARCHAR(50),
    mutation_rate DOUBLE,
    generation_size INT,
    generation_count INT,
    generation_number INT,
    fitness DOUBLE,
    critical_path INT,
    max_fanin INT,
    max_fanout INT,
    ADD_H VARCHAR(50),
    op_number INT,
    node_count INT,
    RCA_number INT,
    CSLA_number INT,
    BE_CSLA_number INT
);


LOAD DATA LOCAL INFILE '/home/casauser/Desktop/mehrshad_vtrflow/ODIN_II/ga_outputs/000/blob_merge/charts/db.csv' INTO TABLE blob_merge_table 
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;
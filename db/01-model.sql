BEGIN TRANSACTION;

DROP TABLE IF EXISTS bins CASCADE;
CREATE TABLE bins (
    pk bigserial NOT NULL,
    bin char(6) NOT NULL,
    brand varchar(255) NOT NULL,
    issuer varchar(255) NOT NULL,
    credit boolean NOT NULL DEFAULT '1',
    created timestamp NOT NULL DEFAULT NOW(),
    updated timestamp NOT NULL DEFAULT NOW(),
    UNIQUE (bin),
    PRIMARY KEY (pk)
);

COMMIT;


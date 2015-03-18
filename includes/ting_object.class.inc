<?php

/**
 * Defines migrating of ting object.
 */
class EasyDDBTingObjectMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBTingObjectMigrationGroup');
    parent::__construct($group);

    // Set table name of source data.
    $table_name = 'ting_object';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'tid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 't',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('ting_object', 't')
              ->fields('t', array('tid', 'vid', 'ding_entity_id'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('tid', 'tid');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('ding_entity_id', 'ding_entity_id');
  }
}

/**
 * Defines migrating of ting_object_revision.
 */
class EasyDDBTingObjectRevisionMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBTingObjectMigrationGroup');
    parent::__construct($group);

    // Set table name of source data.
    $table_name = 'ting_object_revision';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'tid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 't',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('ting_object_revision', 't')
              ->fields('t', array('tid', 'vid', 'timestamp'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('tid', 'tid');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('timestamp', 'timestamp');
  }
}

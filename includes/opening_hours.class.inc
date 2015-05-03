<?php

/**
 * Defines migrating of .
 */
class EasyDDBOpeningHoursMigration extends Migration {

   public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBOpeningHoursMigrationGroup');

    // Set table name of source data.
    $table_name = 'opening_hours';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'instance_id' => array(
          'type' => 'int',
          'not null' => 1,
          'unsigned' => 1,
          'alias' => 'oh',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
      ->select('opening_hours', 'oh');
    $query->innerJoin('node', 'n', 'n.nid=oh.nid');
    $query->fields('oh');
    $query->condition('n.type', 'ding_library');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration('libraryMigration');
    $this->addFieldMapping('date', 'date');
    $this->addFieldMapping('start_time', 'start_time');
    $this->addFieldMapping('end_time', 'end_time');
    $this->addFieldMapping('category_tid', 'category_tid');
    $this->addFieldMapping('notice', 'notice');
    $this->addFieldMapping('repeat_rule', 'repeat_rule');
    $this->addFieldMapping('repeat_end_date', 'repeat_end_date');
    $this->addFieldMapping('original_instance_id', 'original_instance_id')->sourceMigration('openingHoursMigration');
    $this->addFieldMapping('customised', 'customised');
  }
}
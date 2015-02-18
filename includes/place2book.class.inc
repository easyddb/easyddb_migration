<?php
/**
 * Defines migrating of dibs settings.
 */

class EasyDDBPlace2BookMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBPlace2BookMigrationGroup');
    parent::__construct($group);

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'ding_place2book';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
           'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'p',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('ding_place2book', 'p')
              ->fields('p');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('place2book_id', 'place2book_id');
    $this->addFieldMapping('capacity', 'capacity');
    $this->addFieldMapping('maintain_copy', 'maintain_copy')->defaultValue(1);
    $this->addFieldMapping('kultunaut_export', 'kultunaut_export');
    $this->addFieldMapping('passive', 'passive');
  }
}
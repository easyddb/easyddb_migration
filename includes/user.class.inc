<?php
/**
 * @file
 * Implementation of EasyDDBUserMigration.
 */

/**
 * Handling specific to a Drupal 7 source for users.
 */
class EasyDDBRoleMigration extends DrupalRole7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBUserMigrationGroup');
  }
}

/**
 * Handling specific to a Drupal 7 source for users.
 */
class EasyDDBUserMigration extends DrupalUser7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBUserMigrationGroup');
    // Dependencies.
    $this->dependencies[] = 'roleMigration';
  }
}

/**
 * Defines migrating of users tokens.
 */
class EasyDDBUserTokenMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBUserMigrationGroup');
    parent::__construct($group);

    // Dependencies.
    $this->dependencies[] = 'userMigration';

    // Set table name of source data.
    $table_name = 'authmap';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'aid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'a',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('authmap', 'a')
              ->fields('a', array('aid', 'uid', 'authname', 'module'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('authname', 'authname')
      ->dedupe('authmap', 'authname');
    $this->addFieldMapping('module', 'module');
  }
}

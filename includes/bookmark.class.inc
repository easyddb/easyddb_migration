<?php

/**
 * Defines migrating of bookmark.
 */
class EasyDDBBookmarkMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBBookmarkMigrationGroup');

    // Set table name of source data.
    $table_name = 'flags';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'fid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'f',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('flags', 'f')
              ->fields('f', array('fid', 'content_type', 'name', 'title', 'global', 'options'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('content_type', 'content_type');
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('global', 'global');
    $this->addFieldMapping('options', 'options');
  }
}

/**
 * Defines migrating of bookmark types.
 */
class EasyDDBBookmarkTypesMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBBookmarkMigrationGroup');

    // Set table name of source data.
    $table_name = 'flag_types';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'fid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'f',
          ),
        ),
        array(
          'fid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'f',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('flag_types', 'f')
              ->fields('f', array('fid', 'type'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('fid', 'fid');
    $this->addFieldMapping('type', 'type');
  }
}

/**
 * Defines migrating of bookmark counts.
 */
class EasyDDBBookmarkCountsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBBookmarkMigrationGroup');

    // Set table name of source data.
    $table_name = 'flag_counts';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'content_id' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'f',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('flag_counts ', 'f')
              ->fields('f', array('fid', 'content_type', 'content_id', 'count', 'last_updated'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('fid', 'fid');
    $this->addFieldMapping('content_type', 'content_type');
    $this->addFieldMapping('content_id', 'content_id');
    $this->addFieldMapping('count', 'count');
    $this->addFieldMapping('last_updated', 'last_updated');
  }
}

/**
 * Defines migrating of bookmark content.
 */
class EasyDDBBookmarkContentMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBBookmarkMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'userMigration';

    // Set table name of source data.
    $table_name = 'flag_content';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'fcid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'f',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('flag_content ', 'f')
              ->fields('f', array('fcid', 'fid', 'content_type', 'content_id', 'uid', 'sid', 'timestamp'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('fid', 'fid');
    $this->addFieldMapping('content_type', 'content_type');
    $this->addFieldMapping('content_id', 'content_id');
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('sid', 'sid');
    $this->addFieldMapping('timestamp', 'timestamp');
  }
}

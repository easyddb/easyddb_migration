<?php

/**
 * Defines migrating of relation.
 */
class EasyDDBRelationMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Set table name of source data.
    $table_name = 'relation';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'r',
          ),
        ),
         array(
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('relation', 'r')
              ->fields('r');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('relation_type', 'relation_type');
    $this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('arity', 'arity');
  }
}

/**
 * Defines migrating of relation bundle.
 */
class EasyDDBRelationBundlesMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Set table name of source data.
    $table_name = 'relation_bundles';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'relation_type' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
         'entity_type' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
         'bundle' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
          'r_index' => array(
            'type' => 'int',
            'alias' => 'r',
          ),
        ),
        array(
          'relation_type' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
         'entity_type' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
         'bundle' => array(
            'type' => 'varchar',
            'length' => 255,
            'alias' => 'r',
          ),
          'r_index' => array(
            'type' => 'int',
            'alias' => 'r',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('relation_bundles', 'r')
              ->fields('r');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('relation_type', 'relation_type');
    $this->addFieldMapping('entity_type', 'entity_type');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('r_index', 'r_index');
  }
}

/**
 * Defines migrating of relation.
 */
class EasyDDBRelationRevisionMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Set table name of source data.
    $table_name = 'relation_revision';

    // Dependencies.
    $this->dependencies[] = 'relationMigration';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'vid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'r',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('relation_revision', 'r')
              ->fields('r');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('rid', 'rid')->sourceMigration('relationMigration');
    $this->addFieldMapping('relation_type', 'relation_type');
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('arity', 'arity');
  }

  public function complete($e, $r) {
    db_update('relation')
      ->fields(array(
        'vid' => $e->vid
      ))
    ->condition('rid', $e->rid)
    ->execute();
  }
}

/**
 * Defines migrating of relation.
 */
class EasyDDBRelationTypeMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Set table name of source data.
    $table_name = 'relation_type';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'relation_type' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => 1,
            'default' => '',
            'alias' => 'r',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('relation_type', 'r')
              ->fields('r');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('relation_type', 'relation_type');
    $this->addFieldMapping('label', 'label');
    $this->addFieldMapping('reverse_label', 'reverse_label');
    $this->addFieldMapping('directional', 'directional');
    $this->addFieldMapping('transitive', 'transitive');
    $this->addFieldMapping('r_unique', 'r_unique');
    $this->addFieldMapping('min_arity', 'min_arity');
    $this->addFieldMapping('max_arity', 'max_arity');
  }
}

/**
 * Defines migrating of relation.
 */
class EasyDDBEndPointMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'field_data_endpoints';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'entity_type' => array(
            'type' => 'varchar',
            'length' => 128,
            'not null' => 1,
            'default' => '',
            'alias' => 'f',
          ),
          'deleted' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'entity_id' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'revision_id' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'language' => array(
            'type' => 'varchar',
            'length' => 32,
            'not null' => 1,
            'default' => '',
            'alias' => 'f',
          ),
          'delta' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('field_data_endpoints', 'f')
              ->fields('f');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('entity_type', 'entity_type');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('relationMigration');
    $this->addFieldMapping('revision_id', 'revision_id');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('endpoints_entity_type', 'endpoints_entity_type');
    $this->addFieldMapping('endpoints_entity_id', 'endpoints_entity_id');
    $this->addFieldMapping('endpoints_r_index', 'endpoints_r_index');
  }

 public function prepare($e, $r) {
  if ($r->endpoints_entity_type == 'node') {
      // Array of all related migration.
      $sources = array(
          'newsMigration',
          'eventsMigration',
          'libraryMigration',
          'pageMigration',
          'campaignMigration',
      );
      $e->endpoints_entity_id = NULL;
      foreach ($sources as $source) {
        $source_migration = Migration::getInstance($source);
        $source_migration->sourceKeyMap['nid'] = 'nid';
        $destid = $source_migration->getMap()->lookupDestinationID(array($r->endpoints_entity_id));
        if (!empty($destid)) {
          $e->endpoints_entity_id = current($destid);
        }
      }
    }
  }
}

/**
 * Defines migrating of relation.
 */
class EasyDDBEndPointRevisionMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBRelationMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'field_revision_endpoints';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'entity_type' => array(
            'type' => 'varchar',
            'length' => 128,
            'not null' => 1,
            'default' => '',
            'alias' => 'f',
          ),
          'deleted' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'entity_id' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'revision_id' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
          'language' => array(
            'type' => 'varchar',
            'length' => 32,
            'not null' => 1,
            'default' => '',
            'alias' => 'f',
          ),
          'delta' => array(
            'type' => 'int',
            'not null' => 1,
            'default' => 0,
            'alias' => 'f',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('field_revision_endpoints', 'f')
              ->fields('f');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('entity_type', 'entity_type');
    $this->addFieldMapping('bundle', 'bundle');
    $this->addFieldMapping('deleted', 'deleted');
    $this->addFieldMapping('entity_id', 'entity_id')->sourceMigration('relationMigration');
    $this->addFieldMapping('revision_id', 'revision_id')->sourceMigration('relationRevisionMigration');
    $this->addFieldMapping('language', 'language');
    $this->addFieldMapping('delta', 'delta');
    $this->addFieldMapping('endpoints_entity_type', 'endpoints_entity_type');
    $this->addFieldMapping('endpoints_entity_id', 'endpoints_entity_id');
    $this->addFieldMapping('endpoints_r_index', 'endpoints_r_index');
  }

 public function prepare($e, $r) {
  if ($r->endpoints_entity_type == 'node') {
      // Array of all related migration.
      $sources = array(
          'newsMigration',
          'eventsMigration',
          'libraryMigration',
          'pageMigration',
          'campaignMigration',
      );
      $e->endpoints_entity_id = NULL;
      foreach ($sources as $source) {
        $source_migration = Migration::getInstance($source);
        $source_migration->sourceKeyMap['nid'] = 'nid';
        $destid = $source_migration->getMap()->lookupDestinationID(array($r->endpoints_entity_id));
        if (!empty($destid)) {
          $e->endpoints_entity_id = current($destid);
        }
      }
    }
  }

  public function complete($e, $r) {
    db_update('field_data_endpoints')
      ->fields(array(
        'revision_id' => $e->revision_id
      ))
    ->condition('entity_id', $e->entity_id)
    ->execute();
  }
}

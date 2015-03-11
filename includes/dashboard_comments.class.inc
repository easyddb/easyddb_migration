<?php

class EasyDDBEditorialDashboardCommentsMigration extends Migration {
  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBDashboardCommentsMigrationGroup');
    parent::__construct($group);

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';

    // Set table name of source data.
    $table_name = 'editorial_dashboard_comments';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'cid' => array(
          'type' => 'int',
          'not null' => 1,
          'unsigned' => 1,
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
      ->select('dashboard_comments', 'dc');
    $query->leftJoin('node', 'n', 'n.nid=dc.nid');
    $query->condition('n.type', array('ding_event', 'ding_news'), 'IN');
    $query->fields('dc');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('cid', 'cid');
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration'));
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('timestamp', 'timestamp');
    $this->addFieldMapping('comment', 'comment');
  }

  public function preImport() {
    parent::preImport();
    if (!module_exists('easyddb_editorial_dashboard_comments')) {
      throw new MigrateException('Easyddb editorial base comments module not enabled.');
    }
  }
}

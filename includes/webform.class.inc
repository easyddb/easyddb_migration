<?php

/**
 * Defines migrating of webform table.
 */
class EasyDDBWebFormMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');


    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform';

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
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('next_serial', 'next_serial');
    $this->addFieldMapping('confirmation', 'confirmation');
    $this->addFieldMapping('confirmation_format', 'confirmation_format');
    $this->addFieldMapping('redirect_url', 'redirect_url');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('block', 'block');
    $this->addFieldMapping('allow_draft', 'allow_draft');
    $this->addFieldMapping('auto_save', 'auto_save');
    $this->addFieldMapping('submit_notice', 'submit_notice');
    $this->addFieldMapping('submit_text', 'submit_text');
    $this->addFieldMapping('submit_limit', 'submit_limit');
    $this->addFieldMapping('submit_interval', 'submit_interval');
    $this->addFieldMapping('total_submit_limit', 'total_submit_limit');
    $this->addFieldMapping('total_submit_interval', 'total_submit_interval');
    $this->addFieldMapping('progressbar_bar', 'progressbar_bar');
    $this->addFieldMapping('progressbar_page_number', 'progressbar_page_number');
    $this->addFieldMapping('progressbar_percent', 'progressbar_percent');
    $this->addFieldMapping('progressbar_pagebreak_labels', 'progressbar_pagebreak_labels');
    $this->addFieldMapping('progressbar_include_confirmation', 'progressbar_include_confirmation');
    $this->addFieldMapping('progressbar_label_first', 'progressbar_label_first');
    $this->addFieldMapping('progressbar_label_confirmation', 'progressbar_label_confirmation');
    $this->addFieldMapping('preview', 'preview');
    $this->addFieldMapping('preview_next_button_label', 'preview_next_button_label');
    $this->addFieldMapping('preview_prev_button_label', 'preview_prev_button_label');
    $this->addFieldMapping('preview_title', 'preview_title');
    $this->addFieldMapping('preview_message', 'preview_message');
    $this->addFieldMapping('preview_message_format', 'preview_message_format');
    $this->addFieldMapping('preview_excluded_components', 'preview_excluded_components');

  }

  // public function prepareRow($r) {
  //   if (parent::prepareRow($r) === FALSE) {
  //     return FALSE;
  //   }

  //   $r->confirmation = empty($r->confirmation) ? "submit" : $r->confirmation;
  // }
}

/**
 * Defines migrating of webform content table.
 */
class EasyDDBWebFormComponentMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform_component';

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
            'alias' => 'w',
          ),
          'cid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'cid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_component', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('cid', 'cid');
    $this->addFieldMapping('pid', 'pid');
    $this->addFieldMapping('form_key', 'form_key');
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('type', 'type');
    $this->addFieldMapping('value', 'value');
    $this->addFieldMapping('extra', 'extra');
    $this->addFieldMapping('required', 'required');
    $this->addFieldMapping('weight', 'weight');
  }
}

/**
 * Defines migrating of webform_conditional table.
 */
class EasyDDBWebFormConditionalMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform_conditional';

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
            'alias' => 'w',
          ),
          'rgid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'rgid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_conditional', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('rgid', 'rgid');
    $this->addFieldMapping('andor', 'andor');
    $this->addFieldMapping('action', 'action');
    $this->addFieldMapping('target_type', 'target_type');
    $this->addFieldMapping('target', 'target');
    $this->addFieldMapping('weight', 'weight');
  }
}

/**
 * Defines migrating of webform_conditional_rules table.
 */
class EasyDDBWebFormConditionalRulesMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform_conditional_rules';

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
            'alias' => 'w',
          ),
          'rgid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'rgid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_conditional_rules', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('rgid', 'rgid');
    $this->addFieldMapping('rid', 'rid');
    $this->addFieldMapping('source_type', 'source_type');
    $this->addFieldMapping('source', 'source');
    $this->addFieldMapping('operator', 'operator');
    $this->addFieldMapping('value', 'value');

  }
}

/**
 * Defines migrating of webform_emails table.
 */
class EasyDDBWebFormEmailsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform_emails';

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
            'alias' => 'w',
          ),
          'eid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'eid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_emails', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('eid', 'eid');
    $this->addFieldMapping('email', 'email');
    $this->addFieldMapping('subject', 'subject');
    $this->addFieldMapping('from_name', 'from_name');
    $this->addFieldMapping('from_address', 'from_address');
    $this->addFieldMapping('template', 'template');
    $this->addFieldMapping('excluded_components', 'excluded_components');
    $this->addFieldMapping('html', 'html');
    $this->addFieldMapping('attachments', 'attachments');
    $this->addFieldMapping('extra', 'extra');

  }
}

/**
 * Defines migrating of webform_last_download table.
 */
class EasyDDBWebFormLastDownloadMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';
    $this->dependencies[] = 'userMigration';
    $this->dependencies[] = 'webFormSubmissionsMigration';

    // Set table name of source data.
    $table_name = 'webform_last_download';

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
            'alias' => 'w',
          ),
          'uid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
         array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'uid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_last_download', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('sid', 'sid')->sourceMigration('webFormSubmissionsMigration');
    $this->addFieldMapping('requested', 'requested');

  }
}

/**
 * Defines migrating of webform_roles table.
 */
class EasyDDBWebFormRolesMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

     // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';

    // Set table name of source data.
    $table_name = 'webform_roles';

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
            'alias' => 'w',
          ),
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        array(
          'nid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_roles', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('rid', 'rid');
  }
}

/**
 * Defines migrating of webform_submissions table.
 */
class EasyDDBWebFormSubmissionsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

     // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';
    $this->dependencies[] = 'userMigration';

    // Set table name of source data.
    $table_name = 'webform_submissions';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'sid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_submissions', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('serial', 'serial');
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
    $this->addFieldMapping('is_draft', 'is_draft');
    $this->addFieldMapping('submitted', 'submitted');
    $this->addFieldMapping('remote_addr', 'remote_addr');
  }
}

/**
 * Defines migrating of webform_submitted_data table.
 */
class EasyDDBWebFormSubmissionsDataMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBWebFormMigrationGroup');

     // Dependencies.
    $this->dependencies[] = 'newsMigration';
    $this->dependencies[] = 'eventsMigration';
    $this->dependencies[] = 'libraryMigration';
    $this->dependencies[] = 'pageMigration';
    $this->dependencies[] = 'campaignMigration';
    $this->dependencies[] = 'webFormSubmissionsMigration';

    // Set table name of source data.
    $table_name = 'webform_submitted_data';

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
            'alias' => 'w',
          ),
          'sid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'cid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
          'no' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'w',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('webform_submitted_data', 'w')
              ->fields('w');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration(array('newsMigration', 'eventsMigration', 'libraryMigration', 'pageMigration', 'campaignMigration'));
    $this->addFieldMapping('sid', 'sid')->sourceMigration('webFormSubmissionsMigration');
    $this->addFieldMapping('cid', 'cid');
    $this->addFieldMapping('no', 'no');
    $this->addFieldMapping('data', 'data');
  }
}

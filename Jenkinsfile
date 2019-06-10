pipeline {
  triggers {
    cron '''TZ=Europe/Rome
H H * * *'''
  }
  agent {
    docker {
      image "fedora:30"
      args '--user root'
    }
  }
  environment {
    CI = 1
    TX_TOKEN = credentials('transifex-token')
  }
  stages {
    stage('Translations') {
      steps {
        sh 'dnf install -y git transifex-client qt5-qtbase qt5-linguist'
        sh 'curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-push && chmod 755 transifex-push'
        sh 'curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-pull && chmod 755 transifex-pull'
        sh './transifex-push . && ./transifex-pull .'
      }
    }
  }
}

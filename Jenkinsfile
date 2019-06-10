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
        sh "git push --set-upstream origin ${env.GIT_BRANCH}"
        sh 'curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-push && chmod 755 transifex-push'
        sh 'curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/transifex-pull && chmod 755 transifex-pull'
        sh 'curl -O https://raw.githubusercontent.com/lirios/repotools/develop/translations/translate-desktop && chmod 755 translate-desktop'
        sh './transifex-push . && ./transifex-pull .'
        sh 'rm -f transifex-{push,pull}'
      }
    }
  }
}

use octocrab::{Octocrab};
use clap::Parser;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
   /// Name of the organization to fetch repos from
   #[clap(short, long, value_parser)]
   org_name: String,
}

#[tokio::main]
async fn main() -> octocrab::Result<()> {
    let token = std::env::var("GITHUB_TOKEN").expect("Please set the GITHUB_TOKEN environment variable to your github token before using");
    let args = Args::parse();


    let octocrab = Octocrab::builder().personal_token(token.to_string()).build()?;

    let orgs = octocrab.orgs(args.org_name).list_repos().send().await.expect("Repository not found");

    println!("{:?}", orgs);

    Ok(())
}